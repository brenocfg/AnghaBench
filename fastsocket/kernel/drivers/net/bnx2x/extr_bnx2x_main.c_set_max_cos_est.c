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

/* Variables and functions */
#define  BCM57710 148 
#define  BCM57711 147 
#define  BCM57711E 146 
#define  BCM57712 145 
#define  BCM57712_MF 144 
#define  BCM57712_VF 143 
#define  BCM57800 142 
#define  BCM57800_MF 141 
#define  BCM57800_VF 140 
#define  BCM57810 139 
#define  BCM57810_MF 138 
#define  BCM57810_VF 137 
#define  BCM57811 136 
#define  BCM57811_MF 135 
#define  BCM57811_VF 134 
#define  BCM57840_2_20 133 
#define  BCM57840_4_10 132 
#define  BCM57840_MF 131 
#define  BCM57840_MFO 130 
#define  BCM57840_O 129 
#define  BCM57840_VF 128 
 int ENODEV ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int set_max_cos_est(int chip_id)
{
	switch (chip_id) {
	case BCM57710:
	case BCM57711:
	case BCM57711E:
	case BCM57712:
	case BCM57712_MF:
	case BCM57712_VF:
	case BCM57800:
	case BCM57800_MF:
	case BCM57800_VF:
	case BCM57810:
	case BCM57810_MF:
	case BCM57840_4_10:
	case BCM57840_2_20:
	case BCM57840_O:
	case BCM57840_MFO:
	case BCM57810_VF:
	case BCM57840_MF:
	case BCM57840_VF:
	case BCM57811:
	case BCM57811_MF:
	case BCM57811_VF:
		return 1;  /* RHEL: no multi-CoS */
	default:
		pr_err("Unknown board_type (%d), aborting\n", chip_id);
		return -ENODEV;
	}
}