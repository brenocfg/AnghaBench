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
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;

/* Variables and functions */
 int ccv_cnnp_dataframe_extract_value (int /*<<< orphan*/ * const,int const,int const) ; 

int ccv_cnnp_dataframe_extract_tuple(ccv_cnnp_dataframe_t* const dataframe, const int column_idx, const int index)
{
	return ccv_cnnp_dataframe_extract_value(dataframe, column_idx, index * sizeof(void*));
}