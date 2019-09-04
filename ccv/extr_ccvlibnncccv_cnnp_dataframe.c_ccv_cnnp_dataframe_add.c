#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int const stream_type; void* const context; int /*<<< orphan*/  context_deinit; int /*<<< orphan*/  data_deinit; int /*<<< orphan*/  data_enum; } ;
typedef  TYPE_1__ ccv_cnnp_derived_column_data_t ;
struct TYPE_8__ {int column_size; TYPE_4__* derived_column_data; } ;
typedef  TYPE_2__ ccv_cnnp_dataframe_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_enum_f ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_deinit_f ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_context_deinit_f ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 TYPE_4__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_4__*,TYPE_1__*) ; 

int ccv_cnnp_dataframe_add(ccv_cnnp_dataframe_t* const dataframe, ccv_cnnp_column_data_enum_f data_enum, const int stream_type, ccv_cnnp_column_data_deinit_f data_deinit, void* const context, ccv_cnnp_column_data_context_deinit_f context_deinit)
{
	if (!dataframe->derived_column_data)
		dataframe->derived_column_data = ccv_array_new(sizeof(ccv_cnnp_derived_column_data_t), 1, 0);
	ccv_cnnp_derived_column_data_t column_data = {
		.stream_type = stream_type,
		.data_enum = data_enum,
		.data_deinit = data_deinit,
		.context = context,
		.context_deinit = context_deinit,
	};
	ccv_array_push(dataframe->derived_column_data, &column_data);
	return dataframe->column_size + dataframe->derived_column_data->rnum - 1;
}