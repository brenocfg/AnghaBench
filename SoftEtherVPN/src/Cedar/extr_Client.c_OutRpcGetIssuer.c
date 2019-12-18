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
struct TYPE_3__ {int /*<<< orphan*/ * issuer_x; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ RPC_GET_ISSUER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void OutRpcGetIssuer(PACK *p, RPC_GET_ISSUER *c)
{
	BUF *b;
	// Validate arguments
	if (p == NULL || c == NULL)
	{
		return;
	}

	if (c->x != NULL)
	{
		b = XToBuf(c->x, false);

		PackAddBuf(p, "x", b);
		FreeBuf(b);
	}

	if (c->issuer_x != NULL)
	{
		b = XToBuf(c->issuer_x, false);

		PackAddBuf(p, "issuer_x", b);
		FreeBuf(b);
	}
}