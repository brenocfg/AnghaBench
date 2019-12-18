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
struct TYPE_3__ {int sock; } ;
typedef  TYPE_1__ FDHTServerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

void fdht_disconnect_server(FDHTServerInfo *pServer)
{
	if (pServer->sock > 0)
	{
		close(pServer->sock);
		pServer->sock = -1;
	}
}