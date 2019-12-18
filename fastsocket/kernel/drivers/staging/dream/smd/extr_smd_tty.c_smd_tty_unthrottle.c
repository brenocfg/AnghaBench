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
struct tty_struct {struct smd_tty_info* driver_data; } ;
struct smd_tty_info {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  smd_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smd_tty_unthrottle(struct tty_struct *tty)
{
	struct smd_tty_info *info = tty->driver_data;
	smd_kick(info->ch);
}