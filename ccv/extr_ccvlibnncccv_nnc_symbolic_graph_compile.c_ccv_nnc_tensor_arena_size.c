#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int buffer_size; TYPE_1__* buffers; } ;
typedef  TYPE_2__ ccv_nnc_tensor_arena_t ;
struct TYPE_4__ {scalar_t__ size; } ;

/* Variables and functions */

uint64_t ccv_nnc_tensor_arena_size(const ccv_nnc_tensor_arena_t* const tensor_arena)
{
	uint64_t total_size = 0;
	int i;
	for (i = 0; i < tensor_arena->buffer_size; i++)
		total_size += tensor_arena->buffers[i].size;
	return total_size;
}