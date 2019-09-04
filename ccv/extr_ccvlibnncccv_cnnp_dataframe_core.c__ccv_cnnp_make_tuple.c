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
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
struct TYPE_2__ {int size; } ;
typedef  TYPE_1__ ccv_cnnp_dataframe_tuple_t ;

/* Variables and functions */
 void* ccmalloc (int) ; 

__attribute__((used)) static void _ccv_cnnp_make_tuple(void*** const column_data, const int column_size, const int batch_size, void** const data, void* const context, ccv_nnc_stream_context_t* const stream_context)
{
	const ccv_cnnp_dataframe_tuple_t* const tuple = (ccv_cnnp_dataframe_tuple_t*)context;
	int i, j;
	for (i = 0; i < batch_size; i++)
	{
		if (!data[i])
			data[i] = ccmalloc(sizeof(void*) * tuple->size);
		void** tuple_data = (void**)data[i];
		for (j = 0; j < column_size; j++)
			tuple_data[j] = column_data[j][i];
	}
}