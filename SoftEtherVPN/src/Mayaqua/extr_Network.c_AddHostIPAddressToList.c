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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void AddHostIPAddressToList(LIST *o, IP *ip)
{
	IP *r;
	// Validate arguments
	if (o == NULL || ip == NULL)
	{
		return;
	}

	r = Search(o, ip);
	if (r != NULL)
	{
		return;
	}

	Insert(o, Clone(ip, sizeof(IP)));
}