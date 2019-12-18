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
typedef  int uint32_t ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
#define  LPFC_EVT_CODE_FC_10_GBAUD 141 
#define  LPFC_EVT_CODE_FC_16_GBAUD 140 
#define  LPFC_EVT_CODE_FC_1_GBAUD 139 
#define  LPFC_EVT_CODE_FC_2_GBAUD 138 
#define  LPFC_EVT_CODE_FC_4_GBAUD 137 
#define  LPFC_EVT_CODE_FC_8_GBAUD 136 
#define  LPFC_EVT_CODE_FC_NO_LINK 135 
#define  LPFC_EVT_CODE_LINK_100_MBIT 134 
#define  LPFC_EVT_CODE_LINK_10_GBIT 133 
#define  LPFC_EVT_CODE_LINK_10_MBIT 132 
#define  LPFC_EVT_CODE_LINK_1_GBIT 131 
#define  LPFC_EVT_CODE_LINK_NO_LINK 130 
#define  LPFC_TRAILER_CODE_FC 129 
#define  LPFC_TRAILER_CODE_LINK 128 

__attribute__((used)) static uint32_t
lpfc_sli4_port_speed_parse(struct lpfc_hba *phba, uint32_t evt_code,
			   uint8_t speed_code)
{
	uint32_t port_speed;

	switch (evt_code) {
	case LPFC_TRAILER_CODE_LINK:
		switch (speed_code) {
		case LPFC_EVT_CODE_LINK_NO_LINK:
			port_speed = 0;
			break;
		case LPFC_EVT_CODE_LINK_10_MBIT:
			port_speed = 10;
			break;
		case LPFC_EVT_CODE_LINK_100_MBIT:
			port_speed = 100;
			break;
		case LPFC_EVT_CODE_LINK_1_GBIT:
			port_speed = 1000;
			break;
		case LPFC_EVT_CODE_LINK_10_GBIT:
			port_speed = 10000;
			break;
		default:
			port_speed = 0;
		}
		break;
	case LPFC_TRAILER_CODE_FC:
		switch (speed_code) {
		case LPFC_EVT_CODE_FC_NO_LINK:
			port_speed = 0;
			break;
		case LPFC_EVT_CODE_FC_1_GBAUD:
			port_speed = 1000;
			break;
		case LPFC_EVT_CODE_FC_2_GBAUD:
			port_speed = 2000;
			break;
		case LPFC_EVT_CODE_FC_4_GBAUD:
			port_speed = 4000;
			break;
		case LPFC_EVT_CODE_FC_8_GBAUD:
			port_speed = 8000;
			break;
		case LPFC_EVT_CODE_FC_10_GBAUD:
			port_speed = 10000;
			break;
		case LPFC_EVT_CODE_FC_16_GBAUD:
			port_speed = 16000;
			break;
		default:
			port_speed = 0;
		}
		break;
	default:
		port_speed = 0;
	}
	return port_speed;
}