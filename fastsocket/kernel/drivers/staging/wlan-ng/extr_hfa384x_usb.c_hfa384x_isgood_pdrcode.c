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
typedef  int u16 ;

/* Variables and functions */
#define  HFA384x_PDR_3842_NIC_CONFIG 156 
#define  HFA384x_PDR_ALLOWED_CHANNEL 155 
#define  HFA384x_PDR_CFISUPRANGE 154 
#define  HFA384x_PDR_DEFAULT_CHANNEL 153 
#define  HFA384x_PDR_END_OF_PDA 152 
#define  HFA384x_PDR_HFA3861_BASELINE 151 
#define  HFA384x_PDR_HFA3861_CHCALI 150 
#define  HFA384x_PDR_HFA3861_CHCALSP 149 
#define  HFA384x_PDR_HFA3861_IFRF 148 
#define  HFA384x_PDR_HFA3861_MANF_TESTI 147 
#define  HFA384x_PDR_HFA3861_MANF_TESTSP 146 
#define  HFA384x_PDR_HFA3861_SHADOW 145 
#define  HFA384x_PDR_IFR_SETTING 144 
#define  HFA384x_PDR_MAC_ADDRESS 143 
#define  HFA384x_PDR_MFISUPRANGE 142 
#define  HFA384x_PDR_MKK_MEASUREMENTS 141 
#define  HFA384x_PDR_NICID 140 
#define  HFA384x_PDR_NIC_RAMSIZE 139 
#define  HFA384x_PDR_NIC_SERIAL 138 
#define  HFA384x_PDR_PCB_PARTNUM 137 
#define  HFA384x_PDR_PCI_ID 136 
#define  HFA384x_PDR_PCI_IFCONF 135 
#define  HFA384x_PDR_PCI_PMCONF 134 
#define  HFA384x_PDR_PDAVER 133 
#define  HFA384x_PDR_REGDOMAIN 132 
#define  HFA384x_PDR_RFENRGY 131 
#define  HFA384x_PDR_RFR_SETTING 130 
#define  HFA384x_PDR_TEMPTYPE 129 
#define  HFA384x_PDR_USB_ID 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int hfa384x_isgood_pdrcode(u16 pdrcode)
{
	switch (pdrcode) {
	case HFA384x_PDR_END_OF_PDA:
	case HFA384x_PDR_PCB_PARTNUM:
	case HFA384x_PDR_PDAVER:
	case HFA384x_PDR_NIC_SERIAL:
	case HFA384x_PDR_MKK_MEASUREMENTS:
	case HFA384x_PDR_NIC_RAMSIZE:
	case HFA384x_PDR_MFISUPRANGE:
	case HFA384x_PDR_CFISUPRANGE:
	case HFA384x_PDR_NICID:
	case HFA384x_PDR_MAC_ADDRESS:
	case HFA384x_PDR_REGDOMAIN:
	case HFA384x_PDR_ALLOWED_CHANNEL:
	case HFA384x_PDR_DEFAULT_CHANNEL:
	case HFA384x_PDR_TEMPTYPE:
	case HFA384x_PDR_IFR_SETTING:
	case HFA384x_PDR_RFR_SETTING:
	case HFA384x_PDR_HFA3861_BASELINE:
	case HFA384x_PDR_HFA3861_SHADOW:
	case HFA384x_PDR_HFA3861_IFRF:
	case HFA384x_PDR_HFA3861_CHCALSP:
	case HFA384x_PDR_HFA3861_CHCALI:
	case HFA384x_PDR_3842_NIC_CONFIG:
	case HFA384x_PDR_USB_ID:
	case HFA384x_PDR_PCI_ID:
	case HFA384x_PDR_PCI_IFCONF:
	case HFA384x_PDR_PCI_PMCONF:
	case HFA384x_PDR_RFENRGY:
	case HFA384x_PDR_HFA3861_MANF_TESTSP:
	case HFA384x_PDR_HFA3861_MANF_TESTI:
		/* code is OK */
		return 1;
		break;
	default:
		if (pdrcode < 0x1000) {
			/* code is OK, but we don't know exactly what it is */
			pr_debug("Encountered unknown PDR#=0x%04x, "
				 "assuming it's ok.\n", pdrcode);
			return 1;
		} else {
			/* bad code */
			pr_debug("Encountered unknown PDR#=0x%04x, "
				 "(>=0x1000), assuming it's bad.\n", pdrcode);
			return 0;
		}
		break;
	}
	return 0;		/* avoid compiler warnings */
}