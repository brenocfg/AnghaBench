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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 size_t EFAULT ; 
 size_t EINVAL ; 
 scalar_t__ buffer_begin ; 
 scalar_t__ buffer_end ; 
 scalar_t__ copy_from_user (void*,char const*,size_t) ; 
 int /*<<< orphan*/  dac_audio_start_timer () ; 
 int /*<<< orphan*/  dac_audio_sync () ; 
 scalar_t__ data_buffer ; 
 scalar_t__ empty ; 

__attribute__((used)) static ssize_t dac_audio_write(struct file *file, const char *buf, size_t count,
			       loff_t * ppos)
{
	int free;
	int nbytes;

	if (count < 0)
		return -EINVAL;

	if (!count) {
		dac_audio_sync();
		return 0;
	}

	free = buffer_begin - buffer_end;

	if (free < 0)
		free += BUFFER_SIZE;
	if ((free == 0) && (empty))
		free = BUFFER_SIZE;
	if (count > free)
		count = free;
	if (buffer_begin > buffer_end) {
		if (copy_from_user((void *)buffer_end, buf, count))
			return -EFAULT;

		buffer_end += count;
	} else {
		nbytes = data_buffer + BUFFER_SIZE - buffer_end;
		if (nbytes > count) {
			if (copy_from_user((void *)buffer_end, buf, count))
				return -EFAULT;
			buffer_end += count;
		} else {
			if (copy_from_user((void *)buffer_end, buf, nbytes))
				return -EFAULT;
			if (copy_from_user
			    ((void *)data_buffer, buf + nbytes, count - nbytes))
				return -EFAULT;
			buffer_end = data_buffer + count - nbytes;
		}
	}

	if (empty) {
		empty = 0;
		dac_audio_start_timer();
	}

	return count;
}