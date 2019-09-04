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
typedef  int UINT ;
struct TYPE_2__ {int /*<<< orphan*/  SeqNo; } ;
typedef  TYPE_1__ RUDP_SEGMENT ;

/* Variables and functions */
 int COMPARE_RET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int RUDPCompareSegmentList(void *p1, void *p2)
{
	RUDP_SEGMENT *s1, *s2;
	UINT r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	s1 = *((RUDP_SEGMENT **)p1);
	s2 = *((RUDP_SEGMENT **)p2);
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}

	r = COMPARE_RET(s1->SeqNo, s2->SeqNo);

	return r;
}