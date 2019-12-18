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
struct lpfc_vport {int /*<<< orphan*/  port_state; struct fc_vport* fc_vport; } ;
struct fc_vport {int vport_last_state; int vport_state; } ;
typedef  enum fc_vport_state { ____Placeholder_fc_vport_state } fc_vport_state ;

/* Variables and functions */
#define  FC_VPORT_FABRIC_LOGOUT 133 
#define  FC_VPORT_FABRIC_REJ_WWN 132 
#define  FC_VPORT_FAILED 131 
 int FC_VPORT_INITIALIZING ; 
#define  FC_VPORT_LINKDOWN 130 
#define  FC_VPORT_NO_FABRIC_RSCS 129 
#define  FC_VPORT_NO_FABRIC_SUPP 128 
 int /*<<< orphan*/  LPFC_VPORT_FAILED ; 
 int /*<<< orphan*/  LPFC_VPORT_UNKNOWN ; 

inline void lpfc_vport_set_state(struct lpfc_vport *vport,
				 enum fc_vport_state new_state)
{
	struct fc_vport *fc_vport = vport->fc_vport;

	if (fc_vport) {
		/*
		 * When the transport defines fc_vport_set state we will replace
		 * this code with the following line
		 */
		/* fc_vport_set_state(fc_vport, new_state); */
		if (new_state != FC_VPORT_INITIALIZING)
			fc_vport->vport_last_state = fc_vport->vport_state;
		fc_vport->vport_state = new_state;
	}

	/* for all the error states we will set the invternal state to FAILED */
	switch (new_state) {
	case FC_VPORT_NO_FABRIC_SUPP:
	case FC_VPORT_NO_FABRIC_RSCS:
	case FC_VPORT_FABRIC_LOGOUT:
	case FC_VPORT_FABRIC_REJ_WWN:
	case FC_VPORT_FAILED:
		vport->port_state = LPFC_VPORT_FAILED;
		break;
	case FC_VPORT_LINKDOWN:
		vport->port_state = LPFC_VPORT_UNKNOWN;
		break;
	default:
		/* do nothing */
		break;
	}
}