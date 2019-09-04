#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_convnet_train_param_t ;
typedef  int /*<<< orphan*/  ccv_convnet_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void ccv_convnet_supervised_train(ccv_convnet_t* convnet, ccv_array_t* categorizeds, ccv_array_t* tests, const char* filename, ccv_convnet_train_param_t params)
{
#ifdef HAVE_GSL
#ifdef HAVE_CUDA
	if (convnet->use_cwc_accel)
		cwc_convnet_supervised_train(convnet, categorizeds, tests, filename, params);
	else {
#endif
	int i, j, t;
	gsl_rng_env_setup();
	gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
	int aligned_padding = categorizeds->rnum % params.mini_batch;
	int aligned_rnum = categorizeds->rnum - aligned_padding;
	int* idx = (int*)ccmalloc(sizeof(int) * (categorizeds->rnum + aligned_padding));
	for (i = 0; i < categorizeds->rnum; i++)
		idx[i] = i;
	gsl_ran_shuffle(rng, idx, categorizeds->rnum, sizeof(int));
	// the last layer has to be full connect, thus we can use it as softmax layer
	assert(convnet->layers[convnet->count - 1].type == CCV_CONVNET_FULL_CONNECT);
	int category_count = convnet->layers[convnet->count - 1].net.full_connect.count;
	ccv_convnet_t* update_params = _ccv_convnet_update_new(convnet);
	ccv_convnet_t* momentum = _ccv_convnet_update_new(convnet);
	for (t = 0; t < params.max_epoch; t++)
	{
		for (i = 0; i < aligned_rnum; i++)
		{
			// dropout the first hidden layer
			ccv_categorized_t* categorized = (ccv_categorized_t*)ccv_array_get(categorizeds, idx[i]);
			ccv_convnet_encode(convnet, &categorized->matrix, convnet->acts + convnet->count - 1, 1);
			ccv_dense_matrix_t* softmax = convnet->acts[convnet->count - 1];
			float* dloss = softmax->data.f32;
			_ccv_convnet_compute_softmax(softmax, &softmax, 0);
			assert(softmax->rows == category_count && softmax->cols == 1);
			// this mashes softmax and logistic regression together
			// also, it gives you -D[loss w.r.t. to x_i] (note the negative sign)
			for (j = 0; j < category_count; j++)
				dloss[j] = (j == categorized->c) - dloss[j];
			_ccv_convnet_propagate_loss(convnet, categorized->matrix, softmax, update_params);
			if ((i + 1) % params.mini_batch == 0)
			{
				FLUSH(CCV_CLI_INFO, " - at epoch %03d / %d => stochastic gradient descent at %d / %d", t + 1, params.max_epoch, (i + 1) / params.mini_batch, aligned_rnum / params.mini_batch);
				// update weights
				_ccv_convnet_update(convnet, params.mini_batch, momentum, update_params, params.layer_params);
				_ccv_convnet_update_zero(update_params);
				// compact the convnet to avoid any staled temporary resource
				ccv_convnet_compact(convnet);
			}
		}
		int miss = 0;
		for (i = 0; i < tests->rnum; i++)
		{
			FLUSH(CCV_CLI_INFO, " - at epoch %03d / %d => going through %d / %d for tests", t + 1, params.max_epoch, i + 1, tests->rnum);
			ccv_categorized_t* test = (ccv_categorized_t*)ccv_array_get(tests, i);
			int c = 0;
			_ccv_convnet_classify(convnet, &test->matrix, &c, 1);
			if (c != test->c)
				++miss;
		}
		FLUSH(CCV_CLI_INFO, " - at epoch %03d / %d => with miss rate %.2f%%\n", t + 1, params.max_epoch, miss * 100.0f / tests->rnum);
		if (t + 1 < params.max_epoch)
		{
			// reshuffle the parts we visited and move the rest to the beginning
			memcpy(idx + categorizeds->rnum, idx + aligned_rnum, sizeof(int) * aligned_padding);
			memmove(idx + aligned_padding, idx, sizeof(int) * aligned_rnum);
			memcpy(idx, idx + categorizeds->rnum, sizeof(int) * aligned_padding);
			gsl_ran_shuffle(rng, idx + aligned_padding, aligned_rnum, sizeof(int));
		}
	}
	ccfree(idx);
	ccv_convnet_free(momentum);
	ccv_convnet_free(update_params);
	gsl_rng_free(rng);
#ifdef HAVE_CUDA
	}
#endif
#else
	assert(0 && "ccv_convnet_supervised_train requires GSL library support");
#endif
}