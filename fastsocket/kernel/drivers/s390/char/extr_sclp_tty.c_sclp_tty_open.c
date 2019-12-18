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
struct tty_struct {scalar_t__ low_latency; int /*<<< orphan*/ * driver_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct tty_struct* sclp_tty ; 

__attribute__((used)) static int
sclp_tty_open(struct tty_struct *tty, struct file *filp)
{
	sclp_tty = tty;
	tty->driver_data = NULL;
	tty->low_latency = 0;
	return 0;
}