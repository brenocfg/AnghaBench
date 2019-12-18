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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvc_mutex ; 
 int scroll_dir ; 
 int scroll_interval ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static int pvc_proc_write_scroll(struct file *file, const char *buffer,
			   unsigned long count, void *data)
{
	int origcount = count;
	int cmd = simple_strtol(buffer, NULL, 10);

	mutex_lock(&pvc_mutex);
	if (scroll_interval != 0)
		del_timer(&timer);

	if (cmd == 0) {
		scroll_dir = 0;
		scroll_interval = 0;
	} else {
		if (cmd < 0) {
			scroll_dir = -1;
			scroll_interval = -cmd;
		} else {
			scroll_dir = 1;
			scroll_interval = cmd;
		}
		add_timer(&timer);
	}
	mutex_unlock(&pvc_mutex);

	return origcount;
}