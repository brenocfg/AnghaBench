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
typedef  int /*<<< orphan*/  X ;
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddCa (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 

void CiLoadCACert(CLIENT *c, FOLDER *f)
{
	BUF *b;
	X *x;
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	b = CfgGetBuf(f, "X509");
	if (b == NULL)
	{
		return;
	}

	x = BufToX(b, false);

	AddCa(c->Cedar, x);

	FreeX(x);

	FreeBuf(b);
}