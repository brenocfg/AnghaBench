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
struct ether_addr {int /*<<< orphan*/ * ether_addr_octet; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

char *ether_ntoa_r (const struct ether_addr *p_a, char *x) {
	char *y;
	y = x;
	for (int ii = 0; ii < 6; ii++) {
		x += sprintf (x, ii == 0 ? "%.2X" : ":%.2X", p_a->ether_addr_octet[ii]);
	}
	return y;
}