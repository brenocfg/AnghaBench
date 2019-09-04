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
typedef  int off_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */

__attribute__((used)) static void _ccv_cnnp_extract_value(void*** const column_data, const int column_size, const int batch_size, void** const data, void* const context, ccv_nnc_stream_context_t* const stream_context)
{
	const off_t offset = (off_t)(uintptr_t)context;
	int i;
	for (i = 0; i < batch_size; i++)
	{
		char* const values = (char*)column_data[0][i];
		data[i] = *(void**)(values + offset);
	}
}