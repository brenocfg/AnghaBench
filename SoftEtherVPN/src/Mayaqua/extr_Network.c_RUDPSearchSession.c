#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_8__ {void* YourPort; int /*<<< orphan*/  YourIp; void* MyPort; int /*<<< orphan*/  MyIp; } ;
struct TYPE_7__ {int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_2__ RUDP_SESSION ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 

RUDP_SESSION *RUDPSearchSession(RUDP_STACK *r, IP *my_ip, UINT my_port, IP *your_ip, UINT your_port)
{
	RUDP_SESSION t;
	RUDP_SESSION *se;
	// Validate arguments
	if (r == NULL || my_ip == NULL || your_ip == NULL)
	{
		return NULL;
	}

	Copy(&t.MyIp, my_ip, sizeof(IP));
	t.MyPort = my_port;
	Copy(&t.YourIp, your_ip, sizeof(IP));
	t.YourPort = your_port;

	se = Search(r->SessionList, &t);

	return se;
}