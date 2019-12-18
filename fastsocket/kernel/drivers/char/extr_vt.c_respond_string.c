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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  con_schedule_flip (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void respond_string(const char *p, struct tty_struct *tty)
{
	while (*p) {
		tty_insert_flip_char(tty, *p, 0);
		p++;
	}
	con_schedule_flip(tty);
}