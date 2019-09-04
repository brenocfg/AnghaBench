#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_38__ {float* f32; } ;
struct TYPE_39__ {int rows; int cols; TYPE_5__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ ccv_dense_matrix_t ;
struct TYPE_34__ {int height; int width; } ;
struct TYPE_40__ {int count; scalar_t__ channels; int rows; int cols; TYPE_8__* layers; int /*<<< orphan*/  mean_activity; TYPE_1__ input; } ;
typedef  TYPE_7__ ccv_convnet_t ;
struct TYPE_36__ {int count; } ;
struct TYPE_35__ {int cols; int rows; int channels; } ;
struct TYPE_37__ {TYPE_3__ node; TYPE_2__ matrix; } ;
struct TYPE_41__ {scalar_t__ type; TYPE_4__ input; } ;
typedef  TYPE_8__ ccv_convnet_layer_t ;
struct TYPE_42__ {int id; float confidence; } ;
typedef  TYPE_9__ ccv_classification_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int CCV_32F ; 
 int CCV_C1 ; 
 scalar_t__ CCV_CONVNET_FULL_CONNECT ; 
 int /*<<< orphan*/  CCV_FLIP_X ; 
 scalar_t__ CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCV_INTER_CUBIC ; 
 int CCV_NO_DATA_ALLOC ; 
 int /*<<< orphan*/  _ccv_convnet_compute_softmax_parallel (TYPE_6__*,TYPE_6__**,int /*<<< orphan*/ ) ; 
 int _ccv_convnet_derive_scale (TYPE_7__*,int) ; 
 int _ccv_convnet_find_full_connect (TYPE_7__*) ; 
 int _ccv_convnet_find_scan (TYPE_7__*) ; 
 int /*<<< orphan*/  _ccv_convnet_full_connect_forward_propagate_parallel (TYPE_8__*,TYPE_6__*,TYPE_6__**) ; 
 int /*<<< orphan*/  _ccv_convnet_layer_forward_propagate (TYPE_8__*,TYPE_6__*,TYPE_6__**,int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ccv_convnet_make_output (TYPE_8__*,int,int,int*,int*,int*) ; 
 TYPE_6__* ccv_dense_matrix_new (int,int,int,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_flip (TYPE_6__*,TYPE_6__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_6__*) ; 
 int /*<<< orphan*/  ccv_resample (int /*<<< orphan*/ ,TYPE_6__**,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_slice (TYPE_6__*,int /*<<< orphan*/ **,int,int,int,int,int) ; 
 int /*<<< orphan*/  ccv_subtract (TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__**,int /*<<< orphan*/ ,int) ; 

void ccv_convnet_classify(ccv_convnet_t* convnet, ccv_dense_matrix_t** a, int symmetric, ccv_array_t** ranks, int tops, int batch)
{
#ifdef HAVE_CUDA
	if (convnet->use_cwc_accel)
		cwc_convnet_classify(convnet, a, symmetric, ranks, tops, batch);
	else {
#endif
	int i, j, k, t;
	ccv_dense_matrix_t** b = (ccv_dense_matrix_t**)alloca(sizeof(ccv_dense_matrix_t*) * (convnet->count + 1));
	int scan = _ccv_convnet_find_scan(convnet);
	int scale = _ccv_convnet_derive_scale(convnet, scan);
	int full_connect = _ccv_convnet_find_full_connect(convnet);
	assert(scan >= 0 && scan < convnet->count);
	assert(full_connect >= 0 && full_connect < convnet->count);
	memset(b, 0, sizeof(ccv_dense_matrix_t*) * (convnet->count + 1));
	for (i = 0; i < batch; i++)
	{
		assert(CCV_GET_CHANNEL(a[i]->type) == convnet->channels);
		assert(a[i]->rows == convnet->input.height || a[i]->cols == convnet->input.width);
		assert(a[i]->rows >= convnet->input.height && a[i]->cols >= convnet->input.width);
		// find optimal rows and cols to slice to
		int rows = convnet->rows + ((a[i]->rows - convnet->rows) / scale) * scale;
		int cols = convnet->cols + ((a[i]->cols - convnet->cols) / scale) * scale;
		assert(rows == convnet->input.height || cols == convnet->input.width);
		assert(rows <= a[i]->rows && cols <= a[i]->cols);
		ccv_dense_matrix_t* slice = 0;
		ccv_slice(a[i], (ccv_matrix_t**)&slice, CCV_32F, (a[i]->rows - rows) / 2, (a[i]->cols - cols) / 2, rows, cols);
		ccv_dense_matrix_t* mean_activity = 0;
		// scale mean activity up to be substractable (from this one, the CPU implementation is an approximation of GPU implementation)
		ccv_resample(convnet->mean_activity, &mean_activity, 0, rows, cols, CCV_INTER_CUBIC);
		ccv_subtract(slice, mean_activity, (ccv_matrix_t**)b, CCV_32F);
		ccv_matrix_free(mean_activity);
		ccv_matrix_free(slice);
		// doing the first few layers until the first scan layer
		int out_rows, out_cols, out_partition;
		ccv_dense_matrix_t* c = ccv_dense_matrix_new(5 * (!!symmetric + 1), convnet->layers[full_connect].input.node.count, CCV_32F | CCV_C1, 0, 0);
		for (t = 0; t <= !!symmetric; t++)
		{
			rows = b[0]->rows, cols = b[0]->cols;
			for (j = 0; j < scan + 1; j++)
			{
				ccv_convnet_layer_t* layer = convnet->layers + j;
				ccv_convnet_make_output(layer, rows, cols, &out_rows, &out_cols, &out_partition);
				_ccv_convnet_layer_forward_propagate(layer, b[j], b + j + 1, 0);
				assert(b[j + 1]->rows == out_rows && b[j + 1]->cols == out_cols);
				if (j > 0)
					ccv_matrix_free(b[j]);
				rows = out_rows, cols = out_cols;
			}
			int offsets[5][2] = {
				{0, 0},
				{cols - convnet->layers[scan + 1].input.matrix.cols, 0},
				{(cols - convnet->layers[scan + 1].input.matrix.cols) / 2, (rows - convnet->layers[scan + 1].input.matrix.rows) / 2},
				{0, rows - convnet->layers[scan + 1].input.matrix.rows},
				{cols - convnet->layers[scan + 1].input.matrix.cols, rows - convnet->layers[scan + 1].input.matrix.rows},
			};
			for (k = 0; k < 5; k++)
			{
				ccv_dense_matrix_t* input = 0;
				ccv_convnet_layer_t* layer = convnet->layers + scan + 1;
				ccv_slice(b[scan + 1], (ccv_matrix_t**)&input, CCV_32F, offsets[k][1], offsets[k][0], layer->input.matrix.rows, layer->input.matrix.cols);
				// copy the last layer for full connect compute
				b[full_connect] = ccv_dense_matrix_new(convnet->layers[full_connect].input.matrix.rows, convnet->layers[full_connect].input.matrix.cols, CCV_NO_DATA_ALLOC | CCV_32F | convnet->layers[full_connect].input.matrix.channels, c->data.f32 + (t * 5 + k) * convnet->layers[full_connect].input.node.count, 0);
				for (j = scan + 1; j < full_connect; j++)
				{
					layer = convnet->layers + j;
					_ccv_convnet_layer_forward_propagate(layer, j > scan + 1 ? b[j] : input, b + j + 1, 0);
					if (j > scan + 1)
						ccv_matrix_free(b[j]);
					else
						ccv_matrix_free(input);
				}
				ccv_matrix_free(b[full_connect]);
				// set it to 0
				memset(b + scan + 2, 0, sizeof(ccv_dense_matrix_t*) * (full_connect - scan - 1));
			}
			ccv_matrix_free(b[scan + 1]);
			memset(b + 1, 0, sizeof(ccv_dense_matrix_t*) * (scan + 1));
			if (t < !!symmetric)
				ccv_flip(b[0], &b[0], 0, CCV_FLIP_X);
		}
		ccv_matrix_free(b[0]);
		// now have everything in c, do the last full connect propagate
		b[full_connect] = c;
		for (j = full_connect; j < convnet->count; j++)
		{
			ccv_convnet_layer_t* layer = convnet->layers + j;
			assert(layer->type == CCV_CONVNET_FULL_CONNECT);
			_ccv_convnet_full_connect_forward_propagate_parallel(layer, b[j], b + j + 1);
			ccv_matrix_free(b[j]);
		}
		ccv_dense_matrix_t* softmax = 0;
		_ccv_convnet_compute_softmax_parallel(b[convnet->count], &softmax, 0);
		ccv_matrix_free(b[convnet->count]);
		ranks[i] = ccv_array_new(sizeof(ccv_classification_t), tops, 0);
		float* r = softmax->data.f32;
		assert(tops <= softmax->cols);
		for (j = 0; j < tops; j++)
		{
			float max_val = -1;
			int max_idx = -1;
			for (k = 0; k < softmax->cols; k++)
				if (r[k] >= 0 && r[k] > max_val)
					max_val = r[k], max_idx = k;
			assert(max_idx >= 0);
			r[max_idx] = -1;
			ccv_classification_t classification = {
				.id = max_idx,
				.confidence = max_val / ((!!symmetric + 1) * 5),
			};
			ccv_array_push(ranks[i], &classification);
		}
		ccv_matrix_free(softmax);
		memset(b, 0, sizeof(ccv_dense_matrix_t*) * (convnet->count + 1));
	}
#ifdef HAVE_CUDA
	}
#endif
}