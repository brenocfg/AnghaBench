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
 int /*<<< orphan*/  tty_write (struct file*,char*,int) ; 

__attribute__((used)) static void poll_channel(struct file *f, int channel)
{
	char cmd;

	cmd = 0x60 | (channel & 0x1f);
	tty_write(f, &cmd, 1);
}