#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ IPV6_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  IPToStr6Array (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IP6AddrToStr(char *str, UINT size, IPV6_ADDR *addr)
{
	// Validate arguments
	if (str == NULL || addr == NULL)
	{
		return;
	}

	IPToStr6Array(str, size, addr->Value);
}