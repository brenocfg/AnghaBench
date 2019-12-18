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

/* Variables and functions */
 int VIOMAJOR_SUBTYPE_SHIFT ; 
 int VIO_MAX_SUBTYPES ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 void* event_buffer ; 
 int /*<<< orphan*/ * event_buffer_available ; 

void *vio_get_event_buffer(int subtype)
{
	subtype = subtype >> VIOMAJOR_SUBTYPE_SHIFT;
	if ((subtype < 0) || (subtype >= VIO_MAX_SUBTYPES))
		return NULL;

	if (atomic_dec_if_positive(&event_buffer_available[subtype]) == 0)
		return &event_buffer[subtype * 256];
	else
		return NULL;
}