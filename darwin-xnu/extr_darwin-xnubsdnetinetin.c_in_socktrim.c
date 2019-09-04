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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; } ;
typedef  scalar_t__ ap ;

/* Variables and functions */

__attribute__((used)) static void
in_socktrim(struct sockaddr_in *ap)
{
	char *cplim = (char *)&ap->sin_addr;
	char *cp = (char *)(&ap->sin_addr + 1);

	ap->sin_len = 0;
	while (--cp >= cplim)
		if (*cp) {
			(ap)->sin_len = cp - (char *)(ap) + 1;
			break;
		}
}