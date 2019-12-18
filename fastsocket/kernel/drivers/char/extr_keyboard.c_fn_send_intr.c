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
struct vc_data {struct tty_struct* vc_tty; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  con_schedule_flip (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fn_send_intr(struct vc_data *vc)
{
	struct tty_struct *tty = vc->vc_tty;

	if (!tty)
		return;
	tty_insert_flip_char(tty, 0, TTY_BREAK);
	con_schedule_flip(tty);
}