#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int* std; } ;
struct TYPE_7__ {TYPE_1__ normalize; scalar_t__ seed; } ;
typedef  TYPE_2__ ccv_cnnp_random_jitter_t ;
struct TYPE_8__ {int datatype; TYPE_2__ random_jitter; int /*<<< orphan*/  sfmt; } ;
typedef  TYPE_3__ ccv_cnnp_random_jitter_context_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_context_deinit_f ;

/* Variables and functions */
 int const CCV_32F ; 
 int /*<<< orphan*/  COLUMN_ID_LIST (int const) ; 
 int /*<<< orphan*/  _ccv_cnnp_image_deinit ; 
 int /*<<< orphan*/  _ccv_cnnp_random_jitter ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccfree ; 
 scalar_t__ ccmalloc (int) ; 
 int ccv_cnnp_dataframe_map (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfmt_init_gen_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ccv_cnnp_dataframe_image_random_jitter(ccv_cnnp_dataframe_t* const dataframe, const int column_idx, const int datatype, const ccv_cnnp_random_jitter_t random_jitter)
{
	assert(datatype == CCV_32F);
	ccv_cnnp_random_jitter_context_t* const random_jitter_context = (ccv_cnnp_random_jitter_context_t*)ccmalloc(sizeof(ccv_cnnp_random_jitter_context_t));
	if (random_jitter.seed)
		sfmt_init_gen_rand(&random_jitter_context->sfmt, (uint32_t)random_jitter.seed);
	else
		sfmt_init_gen_rand(&random_jitter_context->sfmt, (uint32_t)(uintptr_t)dataframe);
	random_jitter_context->datatype = datatype;
	random_jitter_context->random_jitter = random_jitter;
	int i;
	// The std in the random jitter should be inv_std.
	for (i = 0; i < 3; i++)
		random_jitter_context->random_jitter.normalize.std[i] = random_jitter_context->random_jitter.normalize.std[i] ? 1. / random_jitter_context->random_jitter.normalize.std[i] : 1;
	return ccv_cnnp_dataframe_map(dataframe, _ccv_cnnp_random_jitter, 0, _ccv_cnnp_image_deinit, COLUMN_ID_LIST(column_idx), random_jitter_context, (ccv_cnnp_column_data_context_deinit_f)ccfree);
}