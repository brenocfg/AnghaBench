#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; } ;
typedef  TYPE_1__ ccv_cnnp_dataframe_tuple_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;

/* Variables and functions */
 scalar_t__ ccv_cnnp_dataframe_column_context (int /*<<< orphan*/  const* const,int const) ; 

int ccv_cnnp_dataframe_tuple_size(const ccv_cnnp_dataframe_t* const dataframe, const int column_idx)
{
	const ccv_cnnp_dataframe_tuple_t* const tuple = (ccv_cnnp_dataframe_tuple_t*)ccv_cnnp_dataframe_column_context(dataframe, column_idx);
	return tuple->size;
}