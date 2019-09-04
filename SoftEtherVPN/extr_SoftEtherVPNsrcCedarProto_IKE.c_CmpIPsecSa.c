#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Spi; int /*<<< orphan*/  ServerToClient; } ;
typedef  TYPE_1__ IPSECSA ;

/* Variables and functions */
 int COMPARE_RET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CmpIPsecSa(void *p1, void *p2)
{
	IPSECSA *sa1, *sa2;
	int r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	sa1 = *(IPSECSA **)p1;
	sa2 = *(IPSECSA **)p2;
	if (sa1 == NULL || sa2 == NULL)
	{
		return 0;
	}

	r = COMPARE_RET(sa1->ServerToClient, sa2->ServerToClient);
	if (r != 0)
	{
		return r;
	}

	r = COMPARE_RET(sa1->Spi, sa2->Spi);

	return r;
}