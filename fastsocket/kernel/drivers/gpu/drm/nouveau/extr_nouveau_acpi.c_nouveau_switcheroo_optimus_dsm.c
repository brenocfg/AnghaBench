#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dhandle; int /*<<< orphan*/  optimus_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_DSM_OPTIMUS_ARGS ; 
 int /*<<< orphan*/  NOUVEAU_DSM_OPTIMUS_FN ; 
 TYPE_1__ nouveau_dsm_priv ; 
 int /*<<< orphan*/  nouveau_optimus_dsm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nouveau_switcheroo_optimus_dsm(void)
{
	u32 result = 0;
	if (!nouveau_dsm_priv.optimus_detected)
		return;

	nouveau_optimus_dsm(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_OPTIMUS_FN,
		NOUVEAU_DSM_OPTIMUS_ARGS, &result);
}