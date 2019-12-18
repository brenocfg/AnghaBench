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
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ ccv_cnnp_dataframe_tuple_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_context_deinit_f ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_cnnp_make_tuple ; 
 int /*<<< orphan*/  _ccv_cnnp_tuple_deinit ; 
 scalar_t__ ccfree ; 
 scalar_t__ ccmalloc (int) ; 
 int ccv_cnnp_dataframe_map (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const* const,int const,TYPE_1__* const,int /*<<< orphan*/ ) ; 

int ccv_cnnp_dataframe_make_tuple(ccv_cnnp_dataframe_t* const dataframe, const int* const column_idxs, const int column_idx_size)
{
	ccv_cnnp_dataframe_tuple_t* const tuple = (ccv_cnnp_dataframe_tuple_t*)ccmalloc(sizeof(ccv_cnnp_dataframe_tuple_t));
	tuple->size = column_idx_size;
	return ccv_cnnp_dataframe_map(dataframe, _ccv_cnnp_make_tuple, 0, _ccv_cnnp_tuple_deinit, column_idxs, column_idx_size, tuple, (ccv_cnnp_column_data_context_deinit_f)ccfree);
}