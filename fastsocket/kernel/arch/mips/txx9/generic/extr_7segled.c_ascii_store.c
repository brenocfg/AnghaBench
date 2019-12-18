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
struct sysdev_attribute {int dummy; } ;
struct sys_device {unsigned int id; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  txx9_7segled_putc (unsigned int,char const) ; 

__attribute__((used)) static ssize_t ascii_store(struct sys_device *dev,
			   struct sysdev_attribute *attr,
			   const char *buf, size_t size)
{
	unsigned int ch = dev->id;
	txx9_7segled_putc(ch, buf[0]);
	return size;
}