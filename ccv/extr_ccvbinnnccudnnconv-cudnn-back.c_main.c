#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsfmt_t ;
struct TYPE_12__ {int* f32; } ;
struct TYPE_13__ {TYPE_1__ data; int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_14__ {scalar_t__ backend; int algorithm; int /*<<< orphan*/  info; } ;
typedef  TYPE_3__ ccv_nnc_cmd_t ;

/* Variables and functions */
 int BATCH_SIZE ; 
 scalar_t__ CCV_NNC_BACKEND_CPU_REF ; 
 void* CCV_NNC_BACKEND_GPU_CUDNN ; 
 scalar_t__ CCV_NNC_BACKEND_GPU_REF ; 
 int /*<<< orphan*/  CCV_NNC_DATA_TRANSFER_FORWARD ; 
 scalar_t__ CCV_NNC_EXEC_SUCCESS ; 
 int /*<<< orphan*/  CCV_NNC_FORMAT_TRANSFORM_FORWARD ; 
 int /*<<< orphan*/  CCV_STREAM_CONTEXT_GPU ; 
 TYPE_3__ CMD_CONVOLUTION_FORWARD (int,int,int,int,int) ; 
 int /*<<< orphan*/  CPU_TENSOR_NHWC (int,...) ; 
 int /*<<< orphan*/  GPU_TENSOR_NCHW (int,int,int,int,int) ; 
 int /*<<< orphan*/  GPU_TENSOR_NHWC (int,int,...) ; 
 int INPUT_DIM ; 
 int INPUT_SIZE ; 
 int KERNEL_SIZE ; 
 int OUTPUT_DIM ; 
 int OUTPUT_SIZE ; 
 int /*<<< orphan*/  TENSOR_LIST (TYPE_2__*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_max (int,int) ; 
 TYPE_3__ ccv_nnc_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_auto ; 
 TYPE_3__ ccv_nnc_cmd_autotune (TYPE_3__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ccv_nnc_cmd_exec (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_nnc_hint_auto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_nnc_hint_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_init () ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 
 int /*<<< orphan*/  ccv_nnc_stream_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ccv_nnc_stream_context_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_stream_context_wait (int /*<<< orphan*/ *) ; 
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
	ccv_nnc_tensor_t* a = ccv_nnc_tensor_new(0, CPU_TENSOR_NHWC(INPUT_DIM, INPUT_SIZE, INPUT_SIZE, BATCH_SIZE), 0);
	ccv_nnc_tensor_t* b = ccv_nnc_tensor_new(0, CPU_TENSOR_NHWC(OUTPUT_DIM, OUTPUT_SIZE, OUTPUT_SIZE, BATCH_SIZE), 0);
	ccv_nnc_cmd_t cmd = CMD_CONVOLUTION_FORWARD(1, OUTPUT_DIM, INPUT_DIM, KERNEL_SIZE, KERNEL_SIZE);
	cmd.backend = CCV_NNC_BACKEND_CPU_REF;
	assert(cmd.backend >= 0);
	ccv_nnc_hint_t hint = ccv_nnc_hint_auto(cmd.info, a->info, b->info);
	assert(ccv_nnc_hint_verify(hint, cmd.info, a->info, b->info) == 0);
	ccv_nnc_tensor_t* w = ccv_nnc_tensor_new(0, CPU_TENSOR_NHWC(INPUT_DIM, KERNEL_SIZE, KERNEL_SIZE, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* bias = ccv_nnc_tensor_new(0, CPU_TENSOR_NHWC(OUTPUT_DIM), 0);
	// configure the inlets.
	dsfmt_t dsfmt;
	dsfmt_init_gen_rand(&dsfmt, 0);
	int i;
	for (i = 0; i < INPUT_DIM * KERNEL_SIZE * KERNEL_SIZE * OUTPUT_DIM; i++)
		w->data.f32[i] = dsfmt_genrand_open_close(&dsfmt) / (INPUT_DIM * KERNEL_SIZE * KERNEL_SIZE);
	for (i = 0; i < INPUT_SIZE * INPUT_SIZE * INPUT_DIM * ccv_max(1, BATCH_SIZE); i++)
		a->data.f32[i] = dsfmt_genrand_open_close(&dsfmt);
	for (i = 0; i < OUTPUT_DIM; i++)
		bias->data.f32[i] = (float)i / OUTPUT_DIM;
	// Copy generated matrix values over to GPU.
	ccv_nnc_tensor_t* ga = ccv_nnc_tensor_new(0, GPU_TENSOR_NHWC(000, INPUT_DIM, INPUT_SIZE, INPUT_SIZE, BATCH_SIZE), 0);
	ccv_nnc_tensor_t* gw = ccv_nnc_tensor_new(0, GPU_TENSOR_NHWC(000, INPUT_DIM, KERNEL_SIZE, KERNEL_SIZE, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* gwo = ccv_nnc_tensor_new(0, GPU_TENSOR_NCHW(000, KERNEL_SIZE, KERNEL_SIZE, INPUT_DIM, OUTPUT_DIM), 0);
	ccv_nnc_tensor_t* gbias = ccv_nnc_tensor_new(0, GPU_TENSOR_NHWC(000, OUTPUT_DIM), 0);
	unsigned int elapsed_time = get_current_time();
	ccv_nnc_cmd_t move = ccv_nnc_cmd(CCV_NNC_DATA_TRANSFER_FORWARD, 0, ccv_nnc_cmd_auto, 0);
	move.backend = CCV_NNC_BACKEND_GPU_REF;
	assert(move.backend >= 0);
	ccv_nnc_cmd_exec(move, ccv_nnc_no_hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(ga, gw, gbias), 0);
	ccv_nnc_cmd_exec(cmd, hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(b), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("%u ms for ref\n", elapsed_time);
	ccv_nnc_tensor_t* gc = ccv_nnc_tensor_new(0, GPU_TENSOR_NHWC(000, OUTPUT_DIM, OUTPUT_SIZE, OUTPUT_SIZE, BATCH_SIZE), 0);

	ccv_nnc_cmd_t transform = ccv_nnc_cmd(CCV_NNC_FORMAT_TRANSFORM_FORWARD, 0, ccv_nnc_cmd_auto, 0);
	transform.backend = CCV_NNC_BACKEND_GPU_CUDNN;
	assert(transform.backend >= 0);
	ccv_nnc_stream_context_t* stream_context = ccv_nnc_stream_context_new(CCV_STREAM_CONTEXT_GPU);
	ccv_nnc_cmd_exec(transform, ccv_nnc_no_hint, 0, TENSOR_LIST(gw), TENSOR_LIST(gwo), stream_context);
	ccv_nnc_stream_context_wait(stream_context);
	ccv_nnc_tensor_free(gw);

	cmd.backend = CCV_NNC_BACKEND_GPU_CUDNN;
	assert(cmd.backend >= 0);
	cmd.algorithm = -1;
	cmd = ccv_nnc_cmd_autotune(cmd, 2 * 1024 * 1024 * 1024, hint, 0, TENSOR_LIST(ga, gwo, gbias), TENSOR_LIST(gc), stream_context);
	elapsed_time = get_current_time();
	assert(CCV_NNC_EXEC_SUCCESS == ccv_nnc_cmd_exec(cmd, hint, 0, TENSOR_LIST(ga, gwo, gbias), TENSOR_LIST(gc), stream_context));
	ccv_nnc_stream_context_wait(stream_context);
	ccv_nnc_stream_context_free(stream_context);
	elapsed_time = get_current_time() - elapsed_time;
	printf("%u ms for optimized\n", elapsed_time);
	ccv_nnc_tensor_t* c = ccv_nnc_tensor_new(0, CPU_TENSOR_NHWC(OUTPUT_DIM, OUTPUT_SIZE, OUTPUT_SIZE, BATCH_SIZE), 0);
	ccv_nnc_cmd_exec(move, ccv_nnc_no_hint, 0, TENSOR_LIST(gc), TENSOR_LIST(c), 0);
	for (i = 0; i < OUTPUT_DIM * OUTPUT_SIZE * OUTPUT_SIZE; i++)
		if (fabs(b->data.f32[i] - c->data.f32[i]) > 1e-5)
			printf("%d %f %f\n", i, b->data.f32[i], c->data.f32[i]);
	ccv_nnc_tensor_free(c);
	ccv_nnc_tensor_free(gc);
	ccv_nnc_tensor_free(bias);
	ccv_nnc_tensor_free(w);
	ccv_nnc_tensor_free(b);
	ccv_nnc_tensor_free(a);
	ccv_nnc_tensor_free(gbias);
	ccv_nnc_tensor_free(gwo);
	ccv_nnc_tensor_free(ga);
}