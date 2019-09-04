#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsfmt_t ;
struct TYPE_11__ {int* f32; } ;
struct TYPE_12__ {TYPE_1__ data; int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_13__ {int backend; int algorithm; int /*<<< orphan*/  info; } ;
typedef  TYPE_3__ ccv_nnc_cmd_t ;

/* Variables and functions */
 TYPE_3__ CMD_CONVOLUTION_FORWARD (int,int,int,int,int) ; 
 int INPUT_DIM ; 
 int INPUT_SIZE ; 
 int KERNEL_SIZE ; 
 int /*<<< orphan*/  ONE_CPU_TENSOR (int,...) ; 
 int OUTPUT_DIM ; 
 int OUTPUT_SIZE ; 
 int /*<<< orphan*/  TENSOR_LIST (TYPE_2__*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ ccv_nnc_cmd_autotune (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_exec (TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_hint_auto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_nnc_hint_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_init () ; 
 int /*<<< orphan*/  ccv_nnc_tensor_free (TYPE_2__*) ; 
 TYPE_2__* ccv_nnc_tensor_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsfmt_genrand_open_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsfmt_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fabs (float) ; 
 unsigned int get_current_time () ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int main(int argc, char** argv)
{
	ccv_nnc_init();
	ccv_nnc_tensor_t* a = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(INPUT_SIZE, INPUT_SIZE, INPUT_DIM), 0);
	ccv_nnc_tensor_t* b = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_SIZE, OUTPUT_SIZE, OUTPUT_DIM), 0);
	ccv_nnc_cmd_t cmd = CMD_CONVOLUTION_FORWARD(1, OUTPUT_DIM, KERNEL_SIZE, KERNEL_SIZE, INPUT_DIM);
	ccv_nnc_hint_t hint = ccv_nnc_hint_auto(cmd.info, a->info, b->info);
	assert(ccv_nnc_hint_verify(hint, cmd.info, a->info, b->info) == 0);
	ccv_nnc_tensor_t* w = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM, KERNEL_SIZE, KERNEL_SIZE, INPUT_DIM), 0);
	ccv_nnc_tensor_t* bias = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_DIM), 0);
	// configure the inlets.
	dsfmt_t dsfmt;
	dsfmt_init_gen_rand(&dsfmt, 0);
	int i;
	for (i = 0; i < INPUT_DIM * KERNEL_SIZE * KERNEL_SIZE * OUTPUT_DIM; i++)
		w->data.f32[i] = dsfmt_genrand_open_close(&dsfmt) / (INPUT_DIM * KERNEL_SIZE * KERNEL_SIZE);
	for (i = 0; i < INPUT_SIZE * INPUT_SIZE * INPUT_DIM; i++)
		a->data.f32[i] = dsfmt_genrand_open_close(&dsfmt);
	for (i = 0; i < OUTPUT_DIM; i++)
		bias->data.f32[i] = (float)i / OUTPUT_DIM;
	unsigned int elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(cmd, hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(b), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("%u ms for ref\n", elapsed_time);
	ccv_nnc_tensor_t* c = ccv_nnc_tensor_new(0, ONE_CPU_TENSOR(OUTPUT_SIZE, OUTPUT_SIZE, OUTPUT_DIM), 0);
	ccv_nnc_cmd_t tuned_cmd = ccv_nnc_cmd_autotune(cmd, 0, hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(c), 0);
	elapsed_time = get_current_time();
	ccv_nnc_cmd_exec(tuned_cmd, hint, 0, TENSOR_LIST(a, w, bias), TENSOR_LIST(c), 0);
	elapsed_time = get_current_time() - elapsed_time;
	printf("%u ms for auto-tuned, backend %d, algorithm %d\n", elapsed_time, tuned_cmd.backend, tuned_cmd.algorithm);
	for (i = 0; i < OUTPUT_DIM * OUTPUT_SIZE * OUTPUT_SIZE; i++)
		if (fabs(b->data.f32[i] - c->data.f32[i]) > 1e-5)
			printf("%d %f %f\n", i, b->data.f32[i], c->data.f32[i]);
	ccv_nnc_tensor_free(c);
	ccv_nnc_tensor_free(bias);
	ccv_nnc_tensor_free(w);
	ccv_nnc_tensor_free(b);
	ccv_nnc_tensor_free(a);
}