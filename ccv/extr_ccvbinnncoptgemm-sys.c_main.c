#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsfmt_t ;
struct TYPE_9__ {int* f32; } ;
struct TYPE_10__ {TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
struct TYPE_11__ {scalar_t__ backend; int algorithm; } ;
typedef  TYPE_3__ ccv_nnc_cmd_t ;

/* Variables and functions */
 void* CCV_NNC_BACKEND_CPU_OPT ; 
 int /*<<< orphan*/  CCV_NNC_GEMM_BACKWARD ; 
 int /*<<< orphan*/  CCV_NNC_GEMM_FORWARD ; 
 int /*<<< orphan*/  CMD_GEMM (int) ; 
 int INPUT_DIM ; 
 int /*<<< orphan*/  ONE_CPU_TENSOR (int,...) ; 
 int OUTPUT_DIM ; 
 int /*<<< orphan*/  TENSOR_LIST (TYPE_2__*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ ccv_nnc_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_exec (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_init () ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 
 int /*<<< orphan*/  ccv_nnc_tensor_free (TYPE_2__*) ; 
 TYPE_2__* ccv_nnc_tensor_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsfmt_genrand_open_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsfmt_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fabs (double) ; 
 unsigned int get_current_time () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int main(int argc, char** argv)
{
	ccv_nnc_init();
	ccv_nnc_tensor_t* a = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM), 0);
	ccv_nnc_tensor_t* b = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM), 0);
	ccv_nnc_cmd_t forw_cmd = ccv_nnc_cmd(CCV_NNC_GEMM_FORWARD, 0, CMD_GEMM(OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* w = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* bias = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM), 0);
	// configure the inlets.
	dsfmt_t dsfmt;
	dsfmt_init_gen_rand(&dsfmt, 0);
	int i;
	for (i = 0; i < INPUT_DIM * OUTPUT_DIM; i++)
		w->data.f32[i] = dsfmt_genrand_open_close(&dsfmt) / INPUT_DIM;
	for (i = 0; i < INPUT_DIM; i++)
		a->data.f32[i] = dsfmt_genrand_open_close(&dsfmt);
	for (i = 0; i < OUTPUT_DIM; i++)
		bias->data.f32[i] = (float)i / OUTPUT_DIM;
	unsigned int elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(forw_cmd, ccv_nnc_no_hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(b), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("forw %u ms for ref\n", elapsed_time);
	ccv_nnc_tensor_t* c = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM), 0);
	forw_cmd.backend = CCV_NNC_BACKEND_CPU_OPT;
	assert(forw_cmd.backend >= 0);
	forw_cmd.algorithm = 1; // CCV_NNC_CMD_OPT_FC_ALGO_GEMM = 1
	elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(forw_cmd, ccv_nnc_no_hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(c), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("forw %u ms for optimized\n", elapsed_time);
	for (i = 0; i < OUTPUT_DIM; i++)
		if (fabs(b->data.f32[i] - c->data.f32[i]) > 1e-5)
			printf("forw output[%d]: %f %f\n", i, b->data.f32[i], c->data.f32[i]);
	ccv_nnc_tensor_t* dw = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* h = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM), 0);
	ccv_nnc_cmd_t back_cmd = ccv_nnc_cmd(CCV_NNC_GEMM_BACKWARD, 0, CMD_GEMM(OUTPUT_DIM), 0);
	elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(back_cmd, ccv_nnc_no_hint, 0, TENSOR_LIST(b, a, w), TENSOR_LIST(h, dw, bias), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("back %u ms for ref\n", elapsed_time);
	ccv_nnc_tensor_t* dwc = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* hc = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_DIM), 0);
	ccv_nnc_tensor_t* biasc = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM), 0);
	back_cmd.backend = CCV_NNC_BACKEND_CPU_OPT;
	assert(back_cmd.backend >= 0);
	back_cmd.algorithm = 1; // CCV_NNC_CMD_OPT_FC_ALGO_GEMM = 1
	elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(back_cmd, ccv_nnc_no_hint, 0, TENSOR_LIST(b, a, w), TENSOR_LIST(hc, dwc, biasc), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("back %u ms for optimized\n", elapsed_time);
	for (i = 0; i < OUTPUT_DIM; i++)
		if (fabs(bias->data.f32[i] - biasc->data.f32[i]) > 1e-5)
			printf("back bias[%d]: %f %f\n", i, bias->data.f32[i], biasc->data.f32[i]);
	for (i = 0; i < INPUT_DIM * OUTPUT_DIM; i++)
		if (fabs(dw->data.f32[i] - dwc->data.f32[i]) > 1e-5)
			printf("back dw[%d]: %f %f\n", i, dw->data.f32[i], dwc->data.f32[i]);
	for (i = 0; i < INPUT_DIM; i++)
		if (fabs(h->data.f32[i] - hc->data.f32[i]) > 1e-5)
			printf("back h[%d]: %f %f\n", i, h->data.f32[i], hc->data.f32[i]);
	ccv_nnc_tensor_free(biasc);
	ccv_nnc_tensor_free(dwc);
	ccv_nnc_tensor_free(hc);
	ccv_nnc_tensor_free(c);
	ccv_nnc_tensor_free(bias);
	ccv_nnc_tensor_free(w);
	ccv_nnc_tensor_free(dw);
	ccv_nnc_tensor_free(h);
	ccv_nnc_tensor_free(b);
	ccv_nnc_tensor_free(a);
}