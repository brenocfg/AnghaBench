#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long mode; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  printk (char*) ; 
 unsigned long simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static inline int imm_proc_write(imm_struct *dev, char *buffer, int length)
{
	unsigned long x;

	if ((length > 5) && (strncmp(buffer, "mode=", 5) == 0)) {
		x = simple_strtoul(buffer + 5, NULL, 0);
		dev->mode = x;
		return length;
	}
	printk("imm /proc: invalid variable\n");
	return (-EINVAL);
}