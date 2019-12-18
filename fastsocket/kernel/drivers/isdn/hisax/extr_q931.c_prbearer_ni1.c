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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  prbits (char*,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static
int
prbearer_ni1(char *dest, u_char * p)
{
	char *dp = dest;
	u_char len;

	p++;
	len = *p++;
	dp += sprintf(dp, "    octet 3  ");
	dp += prbits(dp, *p, 8, 8);
	switch (*p++) {
		case 0x80:
			dp += sprintf(dp, " Speech");
			break;
		case 0x88:
			dp += sprintf(dp, " Unrestricted digital information");
			break;
		case 0x90:
			dp += sprintf(dp, " 3.1 kHz audio");
			break;
		default:
			dp += sprintf(dp, " Unknown information-transfer capability");
	}
	*dp++ = '\n';
	dp += sprintf(dp, "    octet 4  ");
	dp += prbits(dp, *p, 8, 8);
	switch (*p++) {
		case 0x90:
			dp += sprintf(dp, " 64 kbps, circuit mode");
			break;
		case 0xc0:
			dp += sprintf(dp, " Packet mode");
			break;
		default:
			dp += sprintf(dp, " Unknown transfer mode");
	}
	*dp++ = '\n';
	if (len > 2) {
		dp += sprintf(dp, "    octet 5  ");
		dp += prbits(dp, *p, 8, 8);
		switch (*p++) {
			case 0x21:
				dp += sprintf(dp, " Rate adaption\n");
				dp += sprintf(dp, "    octet 5a ");
				dp += prbits(dp, *p, 8, 8);
				break;
			case 0xa2:
				dp += sprintf(dp, " u-law");
				break;
			default:
				dp += sprintf(dp, " Unknown UI layer 1 protocol");
		}
		*dp++ = '\n';
	}
	return (dp - dest);
}