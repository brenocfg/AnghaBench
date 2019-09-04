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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Sock; } ;
typedef  TYPE_1__ NOTIFY_CLIENT ;

/* Variables and functions */
 int RecvAll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

bool CcWaitNotify(NOTIFY_CLIENT *n)
{
	UCHAR c;
	// Validate arguments
	if (n == NULL)
	{
		return false;
	}

	// 1 character reception
	if (RecvAll(n->Sock, &c, 1, false) == false)
	{
		// Disconnected
		return false;
	}

	return true;
}