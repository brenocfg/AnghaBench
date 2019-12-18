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
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_acqe_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
#define  LPFC_ASYNC_LINK_SPEED_100MBPS 132 
#define  LPFC_ASYNC_LINK_SPEED_10GBPS 131 
#define  LPFC_ASYNC_LINK_SPEED_10MBPS 130 
#define  LPFC_ASYNC_LINK_SPEED_1GBPS 129 
#define  LPFC_ASYNC_LINK_SPEED_ZERO 128 
 int /*<<< orphan*/  LPFC_LINK_SPEED_10GHZ ; 
 int /*<<< orphan*/  LPFC_LINK_SPEED_1GHZ ; 
 int /*<<< orphan*/  LPFC_LINK_SPEED_UNKNOWN ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_acqe_link*) ; 
 int /*<<< orphan*/  lpfc_acqe_link_speed ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint8_t
lpfc_sli4_parse_latt_link_speed(struct lpfc_hba *phba,
				struct lpfc_acqe_link *acqe_link)
{
	uint8_t link_speed;

	switch (bf_get(lpfc_acqe_link_speed, acqe_link)) {
	case LPFC_ASYNC_LINK_SPEED_ZERO:
	case LPFC_ASYNC_LINK_SPEED_10MBPS:
	case LPFC_ASYNC_LINK_SPEED_100MBPS:
		link_speed = LPFC_LINK_SPEED_UNKNOWN;
		break;
	case LPFC_ASYNC_LINK_SPEED_1GBPS:
		link_speed = LPFC_LINK_SPEED_1GHZ;
		break;
	case LPFC_ASYNC_LINK_SPEED_10GBPS:
		link_speed = LPFC_LINK_SPEED_10GHZ;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0483 Invalid link-attention link speed: x%x\n",
				bf_get(lpfc_acqe_link_speed, acqe_link));
		link_speed = LPFC_LINK_SPEED_UNKNOWN;
		break;
	}
	return link_speed;
}