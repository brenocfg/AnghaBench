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
struct TYPE_2__ {int memory_used; } ;
struct tty_struct {TYPE_1__ buf; } ;

/* Variables and functions */

__attribute__((used)) static int pty_space(struct tty_struct *to)
{
	int n = 8192 - to->buf.memory_used;
	if (n < 0)
		return 0;
	return n;
}