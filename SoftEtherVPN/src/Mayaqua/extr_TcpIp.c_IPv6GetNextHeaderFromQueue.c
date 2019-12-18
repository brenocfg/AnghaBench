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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ UCHAR ;
typedef  int /*<<< orphan*/  QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 scalar_t__ GetNext (int /*<<< orphan*/ *) ; 
 scalar_t__ IPV6_HEADER_NONE ; 

UCHAR IPv6GetNextHeaderFromQueue(QUEUE *q)
{
	UINT *p;
	UCHAR v = 0;
	// Validate arguments
	if (q == NULL)
	{
		return IPV6_HEADER_NONE;
	}

	p = (UINT *)GetNext(q);
	if (p != NULL)
	{
		v = (UCHAR)(*p);
		Free(p);
	}

	return v;
}