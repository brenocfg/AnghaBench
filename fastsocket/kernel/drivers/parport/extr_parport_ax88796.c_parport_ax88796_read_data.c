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
struct parport {int dummy; } ;
struct ax_drvdata {int /*<<< orphan*/  spp_data; } ;

/* Variables and functions */
 struct ax_drvdata* pp_to_drv (struct parport*) ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char
parport_ax88796_read_data(struct parport *p)
{
	struct ax_drvdata *dd = pp_to_drv(p);

	return readb(dd->spp_data);
}