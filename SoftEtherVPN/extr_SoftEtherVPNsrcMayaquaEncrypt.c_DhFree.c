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
struct TYPE_4__ {int /*<<< orphan*/  MyPublicKey; int /*<<< orphan*/  MyPrivateKey; int /*<<< orphan*/  dh; } ;
typedef  TYPE_1__ DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 

void DhFree(DH_CTX *dh)
{
	// Validate arguments
	if (dh == NULL)
	{
		return;
	}

	DH_free(dh->dh);

	FreeBuf(dh->MyPrivateKey);
	FreeBuf(dh->MyPublicKey);

	Free(dh);
}