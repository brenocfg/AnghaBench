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
struct TYPE_2__ {int /*<<< orphan*/  io_mutex; } ;
typedef  TYPE_1__ vwsnd_dev_t ;
struct file {TYPE_1__* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vwsnd_audio_do_write (struct file*,char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t vwsnd_audio_write(struct file *file,
				 const char *buffer,
				 size_t count,
				 loff_t *ppos)
{
	vwsnd_dev_t *devc = file->private_data;
	ssize_t ret;

	mutex_lock(&devc->io_mutex);
	ret = vwsnd_audio_do_write(file, buffer, count, ppos);
	mutex_unlock(&devc->io_mutex);
	return ret;
}