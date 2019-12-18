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
struct hfc_multi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpld_set_reg (struct hfc_multi*,int) ; 
 int /*<<< orphan*/  disablepcibridge (struct hfc_multi*) ; 
 int /*<<< orphan*/  enablepcibridge (struct hfc_multi*) ; 
 unsigned char readpcibridge (struct hfc_multi*,int) ; 
 int /*<<< orphan*/  vpm_write_address (struct hfc_multi*,unsigned short) ; 

inline unsigned char
vpm_in(struct hfc_multi *c, int which, unsigned short addr)
{
	unsigned char res;

	vpm_write_address(c, addr);

	if (!which)
		cpld_set_reg(c, 2);
	else
		cpld_set_reg(c, 3);

	enablepcibridge(c);
	res = readpcibridge(c, 1);
	disablepcibridge(c);

	cpld_set_reg(c, 0);

	return res;
}