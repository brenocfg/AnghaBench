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
struct TYPE_3__ {int /*<<< orphan*/  FirstSock; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpClientSend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * PackError (int /*<<< orphan*/ ) ; 

void ClientUploadNoop(CONNECTION *c)
{
	PACK *p;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	p = PackError(0);
	PackAddInt(p, "noop", 1);
	(void)HttpClientSend(c->FirstSock, p);
	FreePack(p);

	p = HttpClientRecv(c->FirstSock);
	if (p != NULL)
	{
		FreePack(p);
	}
}