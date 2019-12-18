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
struct raw3215_info {scalar_t__ tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_wakeup (scalar_t__) ; 

__attribute__((used)) static void raw3215_wakeup(unsigned long data)
{
	struct raw3215_info *raw = (struct raw3215_info *) data;
	if (raw->tty)
		tty_wakeup(raw->tty);
}