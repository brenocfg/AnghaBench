#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int device_id; } ;
typedef  TYPE_1__ ccv_nnc_stream_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  output_size; int /*<<< orphan*/  outputs; int /*<<< orphan*/  input_size; int /*<<< orphan*/  inputs; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_info_t ;
struct TYPE_9__ {scalar_t__ rnum; } ;
typedef  TYPE_3__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int ccv_nnc_device_ids_for_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int* const,int const) ; 

__attribute__((used)) static int _ccv_nnc_device_ids_for_stream_data(ccv_nnc_graph_exec_info_t* const node, const int device_id, ccv_array_t* const stream_data, int* const device_ids, const int max_device_id_size)
{
	int device_id_size = ccv_nnc_device_ids_for_io(node->inputs, node->input_size, node->outputs, node->output_size, device_ids, max_device_id_size);
	if (device_id_size == 0)
	{
		// If there is a default data, use that device id. Otherwise, use the device id passed in (this will be the default data device id).
		if (stream_data->rnum > 0)
		{
			ccv_nnc_stream_data_t* const default_data = (ccv_nnc_stream_data_t*)ccv_array_get(stream_data, 0);
			device_ids[0] = default_data->device_id;
		} else
			device_ids[0] = device_id >= 0 ? device_id : 0;
		device_id_size = 1;
	}
	return device_id_size;
}