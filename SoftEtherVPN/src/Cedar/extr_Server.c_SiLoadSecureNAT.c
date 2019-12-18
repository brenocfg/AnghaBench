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
typedef  int /*<<< orphan*/  VH_OPTION ;
struct TYPE_4__ {int /*<<< orphan*/  SecureNATOption; } ;
typedef  TYPE_1__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 scalar_t__ CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EnableSecureNAT (TYPE_1__*,int) ; 
 int /*<<< orphan*/  NiLoadVhOptionEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SiLoadSecureNAT(HUB *h, FOLDER *f)
{
	VH_OPTION o;
	// Validate arguments
	if (h == NULL || f == NULL)
	{
		return;
	}

	// Read the VH_OPTION
	NiLoadVhOptionEx(&o, f);

	// Set the VH_OPTION
	Copy(h->SecureNATOption, &o, sizeof(VH_OPTION));

	EnableSecureNAT(h, CfgGetBool(f, "Disabled") ? false : true);
}