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
struct iotlb_entry {int da; int pa; int valid; int pgsz; int endian; int elsz; int mixed; } ;
struct cr_regs {int cam; int ram; } ;

/* Variables and functions */
 int MMU_CAM_PGSZ_MASK ; 
 int MMU_CAM_V ; 
 int MMU_CAM_VATAG_MASK ; 
 int MMU_RAM_ELSZ_MASK ; 
 int MMU_RAM_ENDIAN_MASK ; 
 int MMU_RAM_MIXED ; 
 int MMU_RAM_PADDR_MASK ; 

__attribute__((used)) static void omap2_cr_to_e(struct cr_regs *cr, struct iotlb_entry *e)
{
	e->da		= cr->cam & MMU_CAM_VATAG_MASK;
	e->pa		= cr->ram & MMU_RAM_PADDR_MASK;
	e->valid	= cr->cam & MMU_CAM_V;
	e->pgsz		= cr->cam & MMU_CAM_PGSZ_MASK;
	e->endian	= cr->ram & MMU_RAM_ENDIAN_MASK;
	e->elsz		= cr->ram & MMU_RAM_ELSZ_MASK;
	e->mixed	= cr->ram & MMU_RAM_MIXED;
}