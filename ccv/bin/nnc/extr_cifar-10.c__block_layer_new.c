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
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  MODEL_IO_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _building_block_new (int const,int const,int const,int) ; 
 int /*<<< orphan*/  ccv_cnnp_input () ; 
 int /*<<< orphan*/  ccv_cnnp_model_apply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ccv_cnnp_model_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ccv_cnnp_model_t* _block_layer_new(const int filters, const int strides, const int border, const int blocks)
{
	ccv_cnnp_model_io_t input = ccv_cnnp_input();
	ccv_cnnp_model_t* first_block = _building_block_new(filters, strides, border, 1);
	ccv_cnnp_model_io_t output = ccv_cnnp_model_apply(first_block, MODEL_IO_LIST(input));
	int i;
	for (i = 1; i < blocks; i++)
	{
		ccv_cnnp_model_t* block = _building_block_new(filters, 1, 1, 0);
		output = ccv_cnnp_model_apply(block, MODEL_IO_LIST(output));
	}
	return ccv_cnnp_model_new(MODEL_IO_LIST(input), MODEL_IO_LIST(output), 0);
}