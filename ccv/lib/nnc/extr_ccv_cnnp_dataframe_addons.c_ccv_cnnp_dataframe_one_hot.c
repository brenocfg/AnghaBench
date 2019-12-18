#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int range; int datatype; int format; float onval; float offval; int /*<<< orphan*/  structof; } ;
typedef  TYPE_1__ ccv_cnnp_one_hot_context_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_context_deinit_f ;

/* Variables and functions */
 int const CCV_16F ; 
 int const CCV_32F ; 
 int /*<<< orphan*/  COLUMN_ID_LIST (int const) ; 
 int /*<<< orphan*/  _ccv_cnnp_one_hot ; 
 int /*<<< orphan*/  _ccv_cnnp_tensor_deinit ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccfree ; 
 scalar_t__ ccmalloc (int) ; 
 int ccv_cnnp_dataframe_map (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__* const,int /*<<< orphan*/ ) ; 

int ccv_cnnp_dataframe_one_hot(ccv_cnnp_dataframe_t* const dataframe, const int column_idx, const off_t structof, const int range, const float onval, const float offval, const int datatype, const int format)
{
	assert(datatype == CCV_32F || datatype == CCV_16F);
	ccv_cnnp_one_hot_context_t* const one_hot = (ccv_cnnp_one_hot_context_t*)ccmalloc(sizeof(ccv_cnnp_one_hot_context_t));
	one_hot->range = range;
	one_hot->datatype = datatype;
	one_hot->format = format;
	one_hot->onval = onval;
	one_hot->offval = offval;
	one_hot->structof = structof;
	return ccv_cnnp_dataframe_map(dataframe, _ccv_cnnp_one_hot, 0, _ccv_cnnp_tensor_deinit, COLUMN_ID_LIST(column_idx), one_hot, (ccv_cnnp_column_data_context_deinit_f)ccfree);
}