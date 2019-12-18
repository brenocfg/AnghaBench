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
 int /*<<< orphan*/  cpld_set_reg (struct hfc_multi*,unsigned char) ; 
 int /*<<< orphan*/  disablepcibridge (struct hfc_multi*) ; 
 int /*<<< orphan*/  enablepcibridge (struct hfc_multi*) ; 
 int /*<<< orphan*/  writepcibridge (struct hfc_multi*,int,unsigned char) ; 

inline void
cpld_write_reg(struct hfc_multi *hc, unsigned char reg, unsigned char val)
{
	cpld_set_reg(hc, reg);

	enablepcibridge(hc);
	writepcibridge(hc, 1, val);
	disablepcibridge(hc);

	return;
}