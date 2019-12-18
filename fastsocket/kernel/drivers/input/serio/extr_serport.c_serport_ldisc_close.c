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
struct tty_struct {scalar_t__ disc_data; } ;
struct serport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct serport*) ; 

__attribute__((used)) static void serport_ldisc_close(struct tty_struct *tty)
{
	struct serport *serport = (struct serport *) tty->disc_data;

	kfree(serport);
}