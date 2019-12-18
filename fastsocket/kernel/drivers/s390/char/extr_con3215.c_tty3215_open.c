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
struct tty_struct {int index; scalar_t__ low_latency; struct raw3215_info* driver_data; } ;
struct raw3215_info {struct tty_struct* tty; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int NR_3215 ; 
 struct raw3215_info** raw3215 ; 
 int raw3215_startup (struct raw3215_info*) ; 

__attribute__((used)) static int tty3215_open(struct tty_struct *tty, struct file * filp)
{
	struct raw3215_info *raw;
	int retval, line;

	line = tty->index;
	if ((line < 0) || (line >= NR_3215))
		return -ENODEV;

	raw = raw3215[line];
	if (raw == NULL)
		return -ENODEV;

	tty->driver_data = raw;
	raw->tty = tty;

	tty->low_latency = 0;  /* don't use bottom half for pushing chars */
	/*
	 * Start up 3215 device
	 */
	retval = raw3215_startup(raw);
	if (retval)
		return retval;

	return 0;
}