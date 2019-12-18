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
struct tty_struct {struct acm* driver_data; } ;
struct acm {int writesize; } ;

/* Variables and functions */
 int ACM_NW ; 
 int /*<<< orphan*/  ACM_READY (struct acm*) ; 
 int acm_wb_is_avail (struct acm*) ; 

__attribute__((used)) static int acm_tty_chars_in_buffer(struct tty_struct *tty)
{
	struct acm *acm = tty->driver_data;
	if (!ACM_READY(acm))
		return 0;
	/*
	 * This is inaccurate (overcounts), but it works.
	 */
	return (ACM_NW - acm_wb_is_avail(acm)) * acm->writesize;
}