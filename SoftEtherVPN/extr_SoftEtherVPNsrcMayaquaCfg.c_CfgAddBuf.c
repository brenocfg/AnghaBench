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
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ITEM *CfgAddBuf(FOLDER *f, char *name, BUF *b)
{
	// Validate arguments
	if (f == NULL || name == NULL || b == NULL)
	{
		return NULL;
	}
	return CfgAddByte(f, name, b->Buf, b->Size);
}