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
struct hv_ring_buffer_info {TYPE_1__* ring_buffer; } ;
struct TYPE_2__ {scalar_t__ buffer; } ;

/* Variables and functions */

__attribute__((used)) static inline void *
hv_get_ring_buffer(struct hv_ring_buffer_info *ring_info)
{
	return (void *)ring_info->ring_buffer->buffer;
}