#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ Iv; int IsIvExisting; TYPE_1__* IkeSa; } ;
struct TYPE_4__ {scalar_t__ BlockSize; } ;
typedef  TYPE_2__ IPSECSA ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Zero (scalar_t__,scalar_t__) ; 

void IPsecSaUpdateIv(IPSECSA *sa, void *iv, UINT iv_size)
{
	// Validate arguments
	if (sa == NULL || iv == NULL)
	{
		return;
	}

	Copy(sa->Iv, iv, MIN(sa->IkeSa->BlockSize, iv_size));

	if (iv_size < sa->IkeSa->BlockSize)
	{
		Zero(sa->Iv + sa->IkeSa->BlockSize, sa->IkeSa->BlockSize - iv_size);
	}

	sa->IsIvExisting = true;
}