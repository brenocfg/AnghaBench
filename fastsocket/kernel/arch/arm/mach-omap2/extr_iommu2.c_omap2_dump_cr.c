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
struct iommu {int dummy; } ;
struct cr_regs {int cam; int ram; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t omap2_dump_cr(struct iommu *obj, struct cr_regs *cr, char *buf)
{
	char *p = buf;

	/* FIXME: Need more detail analysis of cam/ram */
	p += sprintf(p, "%08x %08x\n", cr->cam, cr->ram);

	return p - buf;
}