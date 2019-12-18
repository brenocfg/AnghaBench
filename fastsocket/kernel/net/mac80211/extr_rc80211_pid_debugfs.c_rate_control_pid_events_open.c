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
struct rc_pid_event_buffer {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_entry; } ;
struct rc_pid_sta_info {struct rc_pid_event_buffer events; } ;
struct rc_pid_events_file_info {struct rc_pid_event_buffer* events; int /*<<< orphan*/  next_entry; } ;
struct inode {struct rc_pid_sta_info* i_private; } ;
struct file {struct rc_pid_events_file_info* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rc_pid_events_file_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rate_control_pid_events_open(struct inode *inode, struct file *file)
{
	struct rc_pid_sta_info *sinfo = inode->i_private;
	struct rc_pid_event_buffer *events = &sinfo->events;
	struct rc_pid_events_file_info *file_info;
	unsigned long status;

	/* Allocate a state struct */
	file_info = kmalloc(sizeof(*file_info), GFP_KERNEL);
	if (file_info == NULL)
		return -ENOMEM;

	spin_lock_irqsave(&events->lock, status);

	file_info->next_entry = events->next_entry;
	file_info->events = events;

	spin_unlock_irqrestore(&events->lock, status);

	file->private_data = file_info;

	return 0;
}