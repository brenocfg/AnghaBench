#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct lpfc_sli {int dummy; } ;
struct TYPE_11__ {int feaLevelHigh; } ;
struct TYPE_14__ {TYPE_2__ rev; } ;
struct lpfc_hba {int /*<<< orphan*/  fc_pref_ALPA; TYPE_5__ vpd; struct lpfc_sli sli; } ;
typedef  TYPE_5__ lpfc_vpd_t ;
struct TYPE_12__ {int link_flags; int /*<<< orphan*/  fabric_AL_PA; void* link_speed; } ;
struct TYPE_13__ {TYPE_3__ varInitLnk; } ;
struct TYPE_15__ {TYPE_4__ un; int /*<<< orphan*/  mbxOwner; scalar_t__ mbxCommand; } ;
struct TYPE_10__ {TYPE_6__ mb; } ;
struct TYPE_16__ {TYPE_1__ u; } ;
typedef  TYPE_6__ MAILBOX_t ;
typedef  TYPE_7__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FLAGS_IMED_ABORT ; 
 int FLAGS_LINK_SPEED ; 
#define  FLAGS_LOCAL_LB 139 
 int FLAGS_TOPOLOGY_FAILOVER ; 
#define  FLAGS_TOPOLOGY_MODE_LOOP 138 
#define  FLAGS_TOPOLOGY_MODE_LOOP_PT 137 
#define  FLAGS_TOPOLOGY_MODE_PT_LOOP 136 
#define  FLAGS_TOPOLOGY_MODE_PT_PT 135 
 void* LINK_SPEED_10G ; 
 void* LINK_SPEED_16G ; 
 void* LINK_SPEED_1G ; 
 void* LINK_SPEED_2G ; 
 void* LINK_SPEED_4G ; 
 void* LINK_SPEED_8G ; 
 void* LINK_SPEED_AUTO ; 
#define  LPFC_USER_LINK_SPEED_10G 134 
#define  LPFC_USER_LINK_SPEED_16G 133 
#define  LPFC_USER_LINK_SPEED_1G 132 
#define  LPFC_USER_LINK_SPEED_2G 131 
#define  LPFC_USER_LINK_SPEED_4G 130 
#define  LPFC_USER_LINK_SPEED_8G 129 
#define  LPFC_USER_LINK_SPEED_AUTO 128 
 scalar_t__ MBX_INIT_LINK ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_init_link(struct lpfc_hba * phba,
	       LPFC_MBOXQ_t * pmb, uint32_t topology, uint32_t linkspeed)
{
	lpfc_vpd_t *vpd;
	struct lpfc_sli *psli;
	MAILBOX_t *mb;

	mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	psli = &phba->sli;
	switch (topology) {
	case FLAGS_TOPOLOGY_MODE_LOOP_PT:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_LOOP;
		mb->un.varInitLnk.link_flags |= FLAGS_TOPOLOGY_FAILOVER;
		break;
	case FLAGS_TOPOLOGY_MODE_PT_PT:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_PT_PT;
		break;
	case FLAGS_TOPOLOGY_MODE_LOOP:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_LOOP;
		break;
	case FLAGS_TOPOLOGY_MODE_PT_LOOP:
		mb->un.varInitLnk.link_flags = FLAGS_TOPOLOGY_MODE_PT_PT;
		mb->un.varInitLnk.link_flags |= FLAGS_TOPOLOGY_FAILOVER;
		break;
	case FLAGS_LOCAL_LB:
		mb->un.varInitLnk.link_flags = FLAGS_LOCAL_LB;
		break;
	}

	/* Enable asynchronous ABTS responses from firmware */
	mb->un.varInitLnk.link_flags |= FLAGS_IMED_ABORT;

	/* NEW_FEATURE
	 * Setting up the link speed
	 */
	vpd = &phba->vpd;
	if (vpd->rev.feaLevelHigh >= 0x02){
		switch(linkspeed){
		case LPFC_USER_LINK_SPEED_1G:
			mb->un.varInitLnk.link_flags |= FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_1G;
			break;
		case LPFC_USER_LINK_SPEED_2G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_2G;
			break;
		case LPFC_USER_LINK_SPEED_4G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_4G;
			break;
		case LPFC_USER_LINK_SPEED_8G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_8G;
			break;
		case LPFC_USER_LINK_SPEED_10G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_10G;
			break;
		case LPFC_USER_LINK_SPEED_16G:
			mb->un.varInitLnk.link_flags |=	FLAGS_LINK_SPEED;
			mb->un.varInitLnk.link_speed = LINK_SPEED_16G;
			break;
		case LPFC_USER_LINK_SPEED_AUTO:
		default:
			mb->un.varInitLnk.link_speed = LINK_SPEED_AUTO;
			break;
		}

	}
	else
		mb->un.varInitLnk.link_speed = LINK_SPEED_AUTO;

	mb->mbxCommand = (volatile uint8_t)MBX_INIT_LINK;
	mb->mbxOwner = OWN_HOST;
	mb->un.varInitLnk.fabric_AL_PA = phba->fc_pref_ALPA;
	return;
}