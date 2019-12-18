#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_3__ {int status; scalar_t__ c; } ;
struct TYPE_4__ {TYPE_1__ bits; int /*<<< orphan*/  as_long; } ;
typedef  TYPE_2__ srmcons_result ;

/* Variables and functions */
 int /*<<< orphan*/  callback_getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_struct*) ; 

__attribute__((used)) static int
srmcons_do_receive_chars(struct tty_struct *tty)
{
	srmcons_result result;
	int count = 0, loops = 0;

	do {
		result.as_long = callback_getc(0);
		if (result.bits.status < 2) {
			tty_insert_flip_char(tty, (char)result.bits.c, 0);
			count++;
		}
	} while((result.bits.status & 1) && (++loops < 10));

	if (count)
		tty_schedule_flip(tty);

	return count;
}