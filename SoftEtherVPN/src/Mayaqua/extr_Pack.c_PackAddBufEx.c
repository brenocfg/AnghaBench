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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

ELEMENT *PackAddBufEx(PACK *p, char *name, BUF *b, UINT index, UINT total)
{
	// Validate arguments
	if (p == NULL || name == NULL || b == NULL || total == 0)
	{
		return NULL;
	}

	return PackAddDataEx(p, name, b->Buf, b->Size, index, total);
}