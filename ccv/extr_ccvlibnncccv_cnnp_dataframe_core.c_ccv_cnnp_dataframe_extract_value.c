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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_cnnp_extract_value ; 
 int ccv_cnnp_dataframe_map (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int,void*,int /*<<< orphan*/ ) ; 

int ccv_cnnp_dataframe_extract_value(ccv_cnnp_dataframe_t* const dataframe, const int column_idx, const off_t offset)
{
	return ccv_cnnp_dataframe_map(dataframe, _ccv_cnnp_extract_value, 0, 0, &column_idx, 1, (void*)(uintptr_t)offset, 0);
}