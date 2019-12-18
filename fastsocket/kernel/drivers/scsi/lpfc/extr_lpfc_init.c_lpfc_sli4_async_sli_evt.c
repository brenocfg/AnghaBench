#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int lnk_no; } ;
struct lpfc_acqe_sli {int /*<<< orphan*/  event_data1; int /*<<< orphan*/  event_data2; } ;
struct TYPE_4__ {TYPE_1__ lnk_info; struct lpfc_acqe_sli sli_intf; } ;
struct lpfc_hba {char* Port; TYPE_2__ sli4_hba; } ;
struct lpfc_acqe_misconfigured_event {struct lpfc_acqe_sli theEvent; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
#define  LPFC_LINK_NUMBER_0 135 
#define  LPFC_LINK_NUMBER_1 134 
#define  LPFC_LINK_NUMBER_2 133 
#define  LPFC_LINK_NUMBER_3 132 
#define  LPFC_SLI_EVENT_STATUS_NOT_PRESENT 131 
#define  LPFC_SLI_EVENT_STATUS_UNSUPPORTED 130 
#define  LPFC_SLI_EVENT_STATUS_VALID 129 
#define  LPFC_SLI_EVENT_STATUS_WRONG_TYPE 128 
 scalar_t__ LPFC_SLI_EVENT_TYPE_MISCONFIGURED ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_acqe_sli*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,char*,...) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sli_misconfigured_port0 ; 
 int /*<<< orphan*/  lpfc_sli_misconfigured_port1 ; 
 int /*<<< orphan*/  lpfc_sli_misconfigured_port2 ; 
 int /*<<< orphan*/  lpfc_sli_misconfigured_port3 ; 
 int /*<<< orphan*/  lpfc_trailer_type ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
lpfc_sli4_async_sli_evt(struct lpfc_hba *phba, struct lpfc_acqe_sli *acqe_sli)
{
	char port_name;
	char message[128];
	uint8_t status;
	struct lpfc_acqe_misconfigured_event *misconfigured;

	/* special case misconfigured event as it contains data for all ports */
	if ((bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) !=
		 LPFC_SLI_INTF_IF_TYPE_2) ||
		(bf_get(lpfc_trailer_type, acqe_sli) !=
			LPFC_SLI_EVENT_TYPE_MISCONFIGURED)) {
		lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
				"2901 Async SLI event - Event Data1:x%08x Event Data2:"
				"x%08x SLI Event Type:%d\n",
				acqe_sli->event_data1, acqe_sli->event_data2,
				bf_get(lpfc_trailer_type, acqe_sli));
		return;
	}

	port_name = phba->Port[0];
	if (port_name == 0x00)
		port_name = '?'; /* get port name is empty */

	misconfigured = (struct lpfc_acqe_misconfigured_event *)
					&acqe_sli->event_data1;

	/* fetch the status for this port */
	switch (phba->sli4_hba.lnk_info.lnk_no) {
	case LPFC_LINK_NUMBER_0:
		status = bf_get(lpfc_sli_misconfigured_port0,
					&misconfigured->theEvent);
		break;
	case LPFC_LINK_NUMBER_1:
		status = bf_get(lpfc_sli_misconfigured_port1,
					&misconfigured->theEvent);
		break;
	case LPFC_LINK_NUMBER_2:
		status = bf_get(lpfc_sli_misconfigured_port2,
					&misconfigured->theEvent);
		break;
	case LPFC_LINK_NUMBER_3:
		status = bf_get(lpfc_sli_misconfigured_port3,
					&misconfigured->theEvent);
		break;
	default:
		status = ~LPFC_SLI_EVENT_STATUS_VALID;
		break;
	}

	switch (status) {
	case LPFC_SLI_EVENT_STATUS_VALID:
		return; /* no message if the sfp is okay */
	case LPFC_SLI_EVENT_STATUS_NOT_PRESENT:
		sprintf(message, "Optics faulted/incorrectly installed/not " \
				"installed - Reseat optics, if issue not "
				"resolved, replace.");
		break;
	case LPFC_SLI_EVENT_STATUS_WRONG_TYPE:
		sprintf(message,
			"Optics of two types installed - Remove one optic or " \
			"install matching pair of optics.");
		break;
	case LPFC_SLI_EVENT_STATUS_UNSUPPORTED:
		sprintf(message, "Incompatible optics - Replace with " \
				"compatible optics for card to function.");
		break;
	default:
		/* firmware is reporting a status we don't know about */
		sprintf(message, "Unknown event status x%02x", status);
		break;
	}

	lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
			"3176 Misconfigured Physical Port - "
			"Port Name %c %s\n", port_name, message);
}