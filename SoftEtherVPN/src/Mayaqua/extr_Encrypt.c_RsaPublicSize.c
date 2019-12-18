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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Size; } ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* RsaPublicToBuf (int /*<<< orphan*/ *) ; 

UINT RsaPublicSize(K *k)
{
	BUF *b;
	UINT ret;

	b = RsaPublicToBuf(k);
	if (b == NULL)
	{
		return 0;
	}

	ret = b->Size;

	FreeBuf(b);

	return ret;
}