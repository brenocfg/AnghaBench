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
 scalar_t__* cmdline ; 
 size_t len ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,unsigned long) ; 

__attribute__((used)) static int test_write_proc(struct file *file, const char *buffer,
				 unsigned long count, void *data)
{
	if (count >= 256)
		len = 255;
	else
		len = count;

	memcpy(cmdline, buffer, count);
	cmdline[len] = 0;

	return len;
}