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
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ buffer_pos ; 
 int buffer_size ; 
 int buffer_watershed ; 
 int /*<<< orphan*/  event_buffer ; 
 int oprofile_buffer_size ; 
 int oprofile_buffer_watershed ; 
 int /*<<< orphan*/  oprofilefs_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

int alloc_event_buffer(void)
{
	unsigned long flags;

	spin_lock_irqsave(&oprofilefs_lock, flags);
	buffer_size = oprofile_buffer_size;
	buffer_watershed = oprofile_buffer_watershed;
	spin_unlock_irqrestore(&oprofilefs_lock, flags);

	if (buffer_watershed >= buffer_size)
		return -EINVAL;

	buffer_pos = 0;
	event_buffer = vmalloc(sizeof(unsigned long) * buffer_size);
	if (!event_buffer)
		return -ENOMEM;

	return 0;
}