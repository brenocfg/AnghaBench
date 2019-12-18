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
struct TYPE_6__ {TYPE_1__* Session; } ;
struct TYPE_5__ {int /*<<< orphan*/  SessionKey; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int HttpClientSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddClientVersion (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * PackAdditionalConnect (int /*<<< orphan*/ ) ; 

bool ClientUploadAuth2(CONNECTION *c, SOCK *s)
{
	PACK *p = NULL;
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	p = PackAdditionalConnect(c->Session->SessionKey);

	PackAddClientVersion(p, c);

	if (HttpClientSend(s, p) == false)
	{
		FreePack(p);
		return false;
	}
	FreePack(p);

	return true;
}