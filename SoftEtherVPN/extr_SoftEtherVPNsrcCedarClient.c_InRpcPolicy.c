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
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetPolicy (int /*<<< orphan*/ *) ; 

void InRpcPolicy(POLICY *o, PACK *p)
{
	POLICY *pol;
	// Validate arguments
	if (o == NULL || p == NULL)
	{
		return;
	}

	pol = PackGetPolicy(p);
	Copy(o, pol, sizeof(POLICY));
	Free(pol);
}