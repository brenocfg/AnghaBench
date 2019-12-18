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
struct mavenregs {int dummy; } ;
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LR (int) ; 
 int /*<<< orphan*/  cve2_set_reg (struct matrox_fb_info*,int,int) ; 

__attribute__((used)) static void cve2_init_TV(struct matrox_fb_info *minfo,
			 const struct mavenregs *m)
{
	int i;

	LR(0x80);
	LR(0x82); LR(0x83);
	LR(0x84); LR(0x85);
	
	cve2_set_reg(minfo, 0x3E, 0x01);
	
	for (i = 0; i < 0x3E; i++) {
		LR(i);
	}
	cve2_set_reg(minfo, 0x3E, 0x00);
}