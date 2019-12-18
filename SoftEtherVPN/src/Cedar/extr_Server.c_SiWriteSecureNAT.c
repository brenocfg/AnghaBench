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
struct TYPE_3__ {int /*<<< orphan*/  SecureNATOption; scalar_t__ EnableSecureNAT; } ;
typedef  TYPE_1__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  NiWriteVhOptionEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void SiWriteSecureNAT(HUB *h, FOLDER *f)
{
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	CfgAddBool(f, "Disabled", h->EnableSecureNAT ? false : true);

	NiWriteVhOptionEx(h->SecureNATOption, f);
}