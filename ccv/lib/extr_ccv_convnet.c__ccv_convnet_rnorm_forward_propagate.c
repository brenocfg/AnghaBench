#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float* f32; } ;
struct TYPE_16__ {int rows; int cols; TYPE_3__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;
struct TYPE_13__ {int size; float kappa; float alpha; float beta; } ;
struct TYPE_14__ {TYPE_1__ rnorm; } ;
struct TYPE_17__ {TYPE_2__ net; } ;
typedef  TYPE_5__ ccv_convnet_layer_t ;

/* Variables and functions */
 int CCV_32F ; 
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_convnet_make_output (TYPE_5__*,int,int,int*,int*,int*) ; 
 TYPE_4__* ccv_dense_matrix_renew (TYPE_4__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int ccv_max (int,int /*<<< orphan*/ ) ; 
 int ccv_min (int,int) ; 
 float powf (float,float) ; 

__attribute__((used)) static void _ccv_convnet_rnorm_forward_propagate(ccv_convnet_layer_t* layer, ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, ccv_dense_matrix_t** denoms)
{
	int rows, cols, partition;
	ccv_convnet_make_output(layer, a->rows, a->cols, &rows, &cols, &partition);
	int size = layer->net.rnorm.size;
	float kappa = layer->net.rnorm.kappa;
	float alpha = layer->net.rnorm.alpha;
	float beta = layer->net.rnorm.beta;
	int way = size / 2;
	assert(CCV_GET_DATA_TYPE(a->type) == CCV_32F);
	int ch = CCV_GET_CHANNEL(a->type);
	int type = CCV_32F | ch;
	ccv_dense_matrix_t* db = *b = ccv_dense_matrix_renew(*b, rows, cols, type, type, 0);
	int i, j, k, x, p;
	float* ap = a->data.f32;
	float* bp = db->data.f32;
	int ch_per_partition = ch / partition;
	if (denoms)
	{
		ccv_dense_matrix_t* ddenoms = *denoms = ccv_dense_matrix_renew(*denoms, rows, cols, type, type, 0);
		float* dp = ddenoms->data.f32;
		for (i = 0; i < db->rows; i++)
		{
			for (j = 0; j < db->cols; j++)
				for (p = 0; p < partition; p++)
					for (k = 0; k < ch_per_partition; k++)
					{
						float v = ap[j * ch + p * ch_per_partition + k];
						float denom = 0;
						for (x = ccv_max(k - way, 0); x <= ccv_min(k + way, ch_per_partition - 1); x++)
							denom += ap[j * ch + p * ch_per_partition + x] * ap[j * ch + p * ch_per_partition + x];
						denom = kappa + alpha * denom;
						dp[j * ch + p * ch_per_partition + k] = denom;
						bp[j * ch + p * ch_per_partition + k] = v * powf(denom, -beta);
					}
			ap += a->cols * ch;
			dp += ddenoms->cols * ch;
			bp += db->cols * ch;
		}
	} else {
		for (i = 0; i < db->rows; i++)
		{
			for (j = 0; j < db->cols; j++)
				for (p = 0; p < partition; p++)
					for (k = 0; k < ch_per_partition; k++)
					{
						float v = ap[j * ch + p * ch_per_partition + k];
						float denom = 0;
						for (x = ccv_max(k - way, 0); x <= ccv_min(k + way, ch_per_partition - 1); x++)
							denom += ap[j * ch + p * ch_per_partition + x] * ap[j * ch + p * ch_per_partition + x];
						denom = kappa + alpha * denom;
						bp[j * ch + p * ch_per_partition + k] = v * powf(denom, -beta);
					}
			ap += a->cols * ch;
			bp += db->cols * ch;
		}
	}
}