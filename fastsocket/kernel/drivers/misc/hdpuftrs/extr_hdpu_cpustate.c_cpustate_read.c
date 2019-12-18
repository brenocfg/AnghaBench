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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (char*,unsigned char*,int) ; 
 unsigned char cpustate_get_state () ; 

__attribute__((used)) static ssize_t cpustate_read(struct file *file, char *buf,
			     size_t count, loff_t * ppos)
{
	unsigned char data;

	if (count < 0)
		return -EFAULT;
	if (count == 0)
		return 0;

	data = cpustate_get_state();
	if (copy_to_user(buf, &data, sizeof(unsigned char)))
		return -EFAULT;
	return sizeof(unsigned char);
}