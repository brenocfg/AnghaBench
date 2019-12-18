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
struct tty_struct {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *tty_name(struct tty_struct *tty, char *buf)
{
	if (!tty) /* Hmm.  NULL pointer.  That's fun. */
		strcpy(buf, "NULL tty");
	else
		strcpy(buf, tty->name);
	return buf;
}