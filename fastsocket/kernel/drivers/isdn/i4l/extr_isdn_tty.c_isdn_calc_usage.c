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
#define  ISDN_PROTO_L2_FAX 130 
#define  ISDN_PROTO_L2_MODEM 129 
#define  ISDN_PROTO_L2_TRANS 128 
 int ISDN_USAGE_FAX ; 
 int ISDN_USAGE_MODEM ; 
 int ISDN_USAGE_VOICE ; 

__attribute__((used)) static int
isdn_calc_usage(int si, int l2)
{
	int usg = ISDN_USAGE_MODEM;

#ifdef CONFIG_ISDN_AUDIO
	if (si == 1) {
		switch(l2) {
			case ISDN_PROTO_L2_MODEM: 
				usg = ISDN_USAGE_MODEM;
				break;
#ifdef CONFIG_ISDN_TTY_FAX
			case ISDN_PROTO_L2_FAX: 
				usg = ISDN_USAGE_FAX;
				break;
#endif
			case ISDN_PROTO_L2_TRANS: 
			default:
				usg = ISDN_USAGE_VOICE;
				break;
		}
	}
#endif
	return(usg);
}