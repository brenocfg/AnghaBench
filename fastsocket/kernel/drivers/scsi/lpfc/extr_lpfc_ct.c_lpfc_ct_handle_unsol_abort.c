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
struct lpfc_hba {int dummy; } ;
struct hbq_dmabuf {int dummy; } ;

/* Variables and functions */
 int lpfc_bsg_ct_unsol_abort (struct lpfc_hba*,struct hbq_dmabuf*) ; 

int
lpfc_ct_handle_unsol_abort(struct lpfc_hba *phba, struct hbq_dmabuf *dmabuf)
{
	int handled;

	/* CT upper level goes through BSG */
	handled = lpfc_bsg_ct_unsol_abort(phba, dmabuf);

	return handled;
}