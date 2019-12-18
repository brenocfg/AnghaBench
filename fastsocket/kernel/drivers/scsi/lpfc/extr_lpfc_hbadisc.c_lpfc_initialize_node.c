#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int /*<<< orphan*/  phba; } ;
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_5__ {int /*<<< orphan*/  evt_listp; } ;
struct TYPE_4__ {int /*<<< orphan*/  evt_listp; } ;
struct lpfc_nodelist {int /*<<< orphan*/  cmd_qdepth; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  kref; int /*<<< orphan*/  nlp_sid; int /*<<< orphan*/  phba; struct lpfc_vport* vport; int /*<<< orphan*/  nlp_DID; TYPE_3__ nlp_delayfunc; TYPE_2__ dev_loss_evt; TYPE_1__ els_retry_evt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPFC_MAX_TGT_QDEPTH ; 
 int /*<<< orphan*/  NLP_INT_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_NO_SID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_retry_delay ; 

__attribute__((used)) static inline void
lpfc_initialize_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	uint32_t did)
{
	INIT_LIST_HEAD(&ndlp->els_retry_evt.evt_listp);
	INIT_LIST_HEAD(&ndlp->dev_loss_evt.evt_listp);
	init_timer(&ndlp->nlp_delayfunc);
	ndlp->nlp_delayfunc.function = lpfc_els_retry_delay;
	ndlp->nlp_delayfunc.data = (unsigned long)ndlp;
	ndlp->nlp_DID = did;
	ndlp->vport = vport;
	ndlp->phba = vport->phba;
	ndlp->nlp_sid = NLP_NO_SID;
	kref_init(&ndlp->kref);
	NLP_INT_NODE_ACT(ndlp);
	atomic_set(&ndlp->cmd_pending, 0);
	ndlp->cmd_qdepth = LPFC_MAX_TGT_QDEPTH;
}