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
typedef  int uint32_t ;
struct lpfc_hba {int fc_linkspeed; } ;

/* Variables and functions */
#define  LPFC_LINK_SPEED_10GHZ 133 
#define  LPFC_LINK_SPEED_16GHZ 132 
#define  LPFC_LINK_SPEED_1GHZ 131 
#define  LPFC_LINK_SPEED_2GHZ 130 
#define  LPFC_LINK_SPEED_4GHZ 129 
#define  LPFC_LINK_SPEED_8GHZ 128 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 

uint32_t
lpfc_sli_port_speed_get(struct lpfc_hba *phba)
{
	uint32_t link_speed;

	if (!lpfc_is_link_up(phba))
		return 0;

	switch (phba->fc_linkspeed) {
	case LPFC_LINK_SPEED_1GHZ:
		link_speed = 1000;
		break;
	case LPFC_LINK_SPEED_2GHZ:
		link_speed = 2000;
		break;
	case LPFC_LINK_SPEED_4GHZ:
		link_speed = 4000;
		break;
	case LPFC_LINK_SPEED_8GHZ:
		link_speed = 8000;
		break;
	case LPFC_LINK_SPEED_10GHZ:
		link_speed = 10000;
		break;
	case LPFC_LINK_SPEED_16GHZ:
		link_speed = 16000;
		break;
	default:
		link_speed = 0;
	}
	return link_speed;
}