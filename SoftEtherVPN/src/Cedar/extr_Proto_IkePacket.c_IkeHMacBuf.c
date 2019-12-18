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
struct TYPE_4__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  IKE_HASH ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  IkeHMac (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IkeHMacBuf(IKE_HASH *h, void *dst, BUF *key, BUF *data)
{
	// Validate arguments
	if (h == NULL || dst == NULL || key == NULL || data == NULL)
	{
		return;
	}

	IkeHMac(h, dst, key->Buf, key->Size, data->Buf, data->Size);
}