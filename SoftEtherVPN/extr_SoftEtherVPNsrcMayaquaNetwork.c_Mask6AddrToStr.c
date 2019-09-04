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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  Mask6AddrToStrEx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void Mask6AddrToStr(char *str, UINT size, IPV6_ADDR *mask)
{
	Mask6AddrToStrEx(str, size, mask, false);
}