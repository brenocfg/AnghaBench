#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Weight; TYPE_1__* Cedar; } ;
struct TYPE_5__ {int /*<<< orphan*/  CurrentSessions; } ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiCalcPoint (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT SiGetPoint(SERVER *s)
{
	UINT num_session;
	// Validate arguments
	if (s == NULL)
	{
		return 0;
	}

	num_session = Count(s->Cedar->CurrentSessions);

	return SiCalcPoint(s, num_session, s->Weight);
}