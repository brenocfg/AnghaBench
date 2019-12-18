#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* rxd_nrdadr; struct TYPE_2__* rxd_next; void* rxd_rbctrl; } ;
union s_fp_descr {TYPE_1__ r; } ;
typedef  int /*<<< orphan*/  u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMU_CHECK ; 
 int /*<<< orphan*/  DB_GEN (char*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DDI_DMA_SYNC_FORDEV ; 
 int /*<<< orphan*/  DRV_BUF_FLUSH (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_drv_virt2phys (struct s_smc*,void*) ; 

__attribute__((used)) static u_long init_descr_ring(struct s_smc *smc,
			      union s_fp_descr volatile *start,
			      int count)
{
	int i ;
	union s_fp_descr volatile *d1 ;
	union s_fp_descr volatile *d2 ;
	u_long	phys ;

	DB_GEN("descr ring starts at = %x ",(void *)start,0,3) ;
	for (i=count-1, d1=start; i ; i--) {
		d2 = d1 ;
		d1++ ;		/* descr is owned by the host */
		d2->r.rxd_rbctrl = cpu_to_le32(BMU_CHECK) ;
		d2->r.rxd_next = &d1->r ;
		phys = mac_drv_virt2phys(smc,(void *)d1) ;
		d2->r.rxd_nrdadr = cpu_to_le32(phys) ;
	}
	DB_GEN("descr ring ends at = %x ",(void *)d1,0,3) ;
	d1->r.rxd_rbctrl = cpu_to_le32(BMU_CHECK) ;
	d1->r.rxd_next = &start->r ;
	phys = mac_drv_virt2phys(smc,(void *)start) ;
	d1->r.rxd_nrdadr = cpu_to_le32(phys) ;

	for (i=count, d1=start; i ; i--) {
		DRV_BUF_FLUSH(&d1->r,DDI_DMA_SYNC_FORDEV) ;
		d1++;
	}
	return(phys) ;
}