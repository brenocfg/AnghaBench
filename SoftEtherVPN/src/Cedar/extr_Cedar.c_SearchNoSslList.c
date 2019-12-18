#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_9__ {int /*<<< orphan*/  NonSslList; } ;
struct TYPE_8__ {int /*<<< orphan*/  IpAddress; } ;
typedef  TYPE_1__ NON_SSL ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

NON_SSL *SearchNoSslList(CEDAR *c, IP *ip)
{
	NON_SSL *n, t;
	// Validate arguments
	if (c == NULL || ip == NULL)
	{
		return NULL;
	}

	Zero(&t, sizeof(t));
	Copy(&t.IpAddress, ip, sizeof(IP));

	n = Search(c->NonSslList, &t);

	if (n == NULL)
	{
		return NULL;
	}

	return n;
}