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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int StrictMode; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  DestIp; } ;
typedef  TYPE_1__ STORM ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CompareStormList(void *p1, void *p2)
{
	STORM *s1, *s2;
	UINT r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	s1 = *(STORM **)p1;
	s2 = *(STORM **)p2;
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}
	if (s1->StrictMode == false && s2->StrictMode == false)
	{
		// Normal mode
		r = CmpIpAddr(&s1->DestIp, &s2->DestIp);
		if (r != 0)
		{
			return r;
		}
		r = CmpIpAddr(&s1->SrcIp, &s2->SrcIp);
		if (r != 0)
		{
			return r;
		}
	}
	else
	{
		// Strict mode
		int r1, r2;
		r1 = CmpIpAddr(&s1->DestIp, &s2->DestIp);
		r2 = CmpIpAddr(&s1->SrcIp, &s2->SrcIp);
		if (r1 == 0 || r2 == 0)
		{
			// Either the source IP, and destination IP match
		}
		else
		{
			// Mismatch
			if (r1 != 0)
			{
				return r1;
			}

			if (r2 != 0)
			{
				return r2;
			}
		}
	}
	r = Cmp(s1->MacAddress, s2->MacAddress, 6);
	return r;
}