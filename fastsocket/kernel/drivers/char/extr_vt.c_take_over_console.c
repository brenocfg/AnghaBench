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
struct consw {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  bind_con_driver (struct consw const*,int,int,int) ; 
 int register_con_driver (struct consw const*,int,int) ; 

int take_over_console(const struct consw *csw, int first, int last, int deflt)
{
	int err;

	err = register_con_driver(csw, first, last);
	/* if we get an busy error we still want to bind the console driver
	 * and return success, as we may have unbound the console driver
	 * but not unregistered it.
	 */
	if (err == -EBUSY)
		err = 0;
	if (!err)
		bind_con_driver(csw, first, last, deflt);

	return err;
}