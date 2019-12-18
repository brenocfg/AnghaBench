#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_adsp_module {int (* patch_event ) (struct msm_adsp_module*,struct adsp_event*) ;} ;
struct adsp_event {int dummy; } ;

/* Variables and functions */
 int stub1 (struct msm_adsp_module*,struct adsp_event*) ; 

__attribute__((used)) static int adsp_patch_event(struct msm_adsp_module *module,
				struct adsp_event *event)
{
	/* call the per-module msg verifier */
	if (module->patch_event)
		return module->patch_event(module, event);
	return 0;
}