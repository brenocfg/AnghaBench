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
struct wrb_handle {int dummy; } ;
struct hwi_wrb_context {size_t free_index; int /*<<< orphan*/  wrb_handles_available; struct wrb_handle** pwrb_handle_base; } ;
struct TYPE_2__ {int wrbs_per_cxn; } ;
struct beiscsi_hba {TYPE_1__ params; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_IO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,struct wrb_handle*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_wrb_handle(struct beiscsi_hba *phba, struct hwi_wrb_context *pwrb_context,
		struct wrb_handle *pwrb_handle)
{
	pwrb_context->pwrb_handle_base[pwrb_context->free_index] = pwrb_handle;
	pwrb_context->wrb_handles_available++;
	if (pwrb_context->free_index == (phba->params.wrbs_per_cxn - 1))
		pwrb_context->free_index = 0;
	else
		pwrb_context->free_index++;

	beiscsi_log(phba, KERN_INFO,
		    BEISCSI_LOG_IO | BEISCSI_LOG_CONFIG,
		    "BM_%d : FREE WRB: pwrb_handle=%p free_index=0x%x"
		    "wrb_handles_available=%d\n",
		    pwrb_handle, pwrb_context->free_index,
		    pwrb_context->wrb_handles_available);
}