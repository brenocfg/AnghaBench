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
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 unsigned long BBR_CPU ; 
 unsigned long BBR_INST ; 
 unsigned long BBR_READ ; 
 unsigned long BRCR_PCBA ; 
 unsigned long BRCR_PCTE ; 
 scalar_t__ CPU_SH7203 ; 
 scalar_t__ CPU_SH7710 ; 
 scalar_t__ CPU_SH7712 ; 
 scalar_t__ CPU_SH7729 ; 
 int /*<<< orphan*/  UBC_BAMRA ; 
 int /*<<< orphan*/  UBC_BARA ; 
 int /*<<< orphan*/  UBC_BASRA ; 
 int /*<<< orphan*/  UBC_BBRA ; 
 int /*<<< orphan*/  UBC_BRCR ; 
 int /*<<< orphan*/  UBC_CAMR0 ; 
 int /*<<< orphan*/  UBC_CAR0 ; 
 int /*<<< orphan*/  UBC_CBCR ; 
 int /*<<< orphan*/  UBC_CBR0 ; 
 unsigned long UBC_CBR_AIE ; 
 unsigned long UBC_CBR_AIV_SET (int) ; 
 unsigned long UBC_CBR_CE ; 
 unsigned long UBC_CBR_ID_INST ; 
 unsigned long UBC_CBR_RW_READ ; 
 int /*<<< orphan*/  UBC_CRR0 ; 
 unsigned long UBC_CRR_BIE ; 
 unsigned long UBC_CRR_PCB ; 
 unsigned long UBC_CRR_RES ; 
 unsigned long ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ current_cpu_data ; 

__attribute__((used)) static void ubc_set_tracing(int asid, unsigned long pc)
{
#if defined(CONFIG_CPU_SH4A)
	unsigned long val;

	val = (UBC_CBR_ID_INST | UBC_CBR_RW_READ | UBC_CBR_CE);
	val |= (UBC_CBR_AIE | UBC_CBR_AIV_SET(asid));

	ctrl_outl(val, UBC_CBR0);
	ctrl_outl(pc,  UBC_CAR0);
	ctrl_outl(0x0, UBC_CAMR0);
	ctrl_outl(0x0, UBC_CBCR);

	val = (UBC_CRR_RES | UBC_CRR_PCB | UBC_CRR_BIE);
	ctrl_outl(val, UBC_CRR0);

	/* Read UBC register that we wrote last, for checking update */
	val = ctrl_inl(UBC_CRR0);

#else	/* CONFIG_CPU_SH4A */
	ctrl_outl(pc, UBC_BARA);

#ifdef CONFIG_MMU
	ctrl_outb(asid, UBC_BASRA);
#endif

	ctrl_outl(0, UBC_BAMRA);

	if (current_cpu_data.type == CPU_SH7729 ||
	    current_cpu_data.type == CPU_SH7710 ||
	    current_cpu_data.type == CPU_SH7712 ||
	    current_cpu_data.type == CPU_SH7203){
		ctrl_outw(BBR_INST | BBR_READ | BBR_CPU, UBC_BBRA);
		ctrl_outl(BRCR_PCBA | BRCR_PCTE, UBC_BRCR);
	} else {
		ctrl_outw(BBR_INST | BBR_READ, UBC_BBRA);
		ctrl_outw(BRCR_PCBA, UBC_BRCR);
	}
#endif	/* CONFIG_CPU_SH4A */
}