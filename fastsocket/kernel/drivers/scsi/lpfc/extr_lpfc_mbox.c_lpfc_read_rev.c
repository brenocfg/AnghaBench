#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hba {int dummy; } ;
struct TYPE_9__ {int cv; int v3req; } ;
struct TYPE_10__ {TYPE_2__ varRdRev; } ;
struct TYPE_11__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_3__ un; } ;
struct TYPE_8__ {TYPE_4__ mb; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBX_READ_REV ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_read_rev(struct lpfc_hba * phba, LPFC_MBOXQ_t * pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));
	mb->un.varRdRev.cv = 1;
	mb->un.varRdRev.v3req = 1; /* Request SLI3 info */
	mb->mbxCommand = MBX_READ_REV;
	mb->mbxOwner = OWN_HOST;
	return;
}