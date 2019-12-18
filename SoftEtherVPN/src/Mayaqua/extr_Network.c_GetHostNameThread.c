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
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddHostCache (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  AddWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DelWaitThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ GetHostNameInner (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 

void GetHostNameThread(THREAD *t, void *p)
{
	IP *ip;
	char hostname[256];
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	ip = (IP *)p;

	AddWaitThread(t);

	NoticeThreadInit(t);

	if (GetHostNameInner(hostname, sizeof(hostname), ip))
	{
		AddHostCache(ip, hostname);
	}

	Free(ip);

	DelWaitThread(t);
}