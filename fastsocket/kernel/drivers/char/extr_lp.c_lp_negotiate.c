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

/* Variables and functions */
 int IEEE1284_MODE_COMPAT ; 
 scalar_t__ parport_negotiate (struct parport*,int) ; 

__attribute__((used)) static int lp_negotiate(struct parport * port, int mode)
{
	if (parport_negotiate (port, mode) != 0) {
		mode = IEEE1284_MODE_COMPAT;
		parport_negotiate (port, mode);
	}

	return (mode);
}