#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* issuer_x; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ RPC_GET_ISSUER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 void* BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcGetIssuer(RPC_GET_ISSUER *c, PACK *p)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(RPC_GET_ISSUER));
	b = PackGetBuf(p, "x");
	if (b != NULL)
	{
		if (c->x != NULL)
		{
			FreeX(c->x);
		}
		c->x = BufToX(b, false);
		FreeBuf(b);
	}

	b = PackGetBuf(p, "issuer_x");
	if (b != NULL)
	{
		c->issuer_x = BufToX(b, false);
		FreeBuf(b);
	}
}