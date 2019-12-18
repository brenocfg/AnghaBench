#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;
struct TYPE_5__ {TYPE_2__* const context; int /*<<< orphan*/  data_enum; } ;
typedef  TYPE_1__ ccv_cnnp_column_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  rnum; } ;
typedef  TYPE_2__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_cnnp_array_enum ; 
 int /*<<< orphan*/ * ccv_cnnp_dataframe_new (TYPE_1__ const*,int,int /*<<< orphan*/ ) ; 

ccv_cnnp_dataframe_t* ccv_cnnp_dataframe_from_array_new(ccv_array_t* const array)
{
	const ccv_cnnp_column_data_t array_column_data = {
		.data_enum = _ccv_cnnp_array_enum,
		.context = array
	};
	return ccv_cnnp_dataframe_new(&array_column_data, 1, array->rnum);
}