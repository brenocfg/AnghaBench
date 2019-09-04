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
 int /*<<< orphan*/  APR ; 
 int /*<<< orphan*/  DFR ; 
 int /*<<< orphan*/ * DM_str ; 
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  IRR_BASE ; 
 int /*<<< orphan*/  ISR_BASE ; 
 int LAPIC_APR_MASK ; 
 int LAPIC_DFR_SHIFT ; 
 int LAPIC_ID_MASK ; 
 int LAPIC_ID_SHIFT ; 
 int LAPIC_LDR_SHIFT ; 
 size_t LAPIC_LVT_DM_MASK ; 
 size_t LAPIC_LVT_DM_SHIFT ; 
 int LAPIC_LVT_DS_PENDING ; 
 int LAPIC_LVT_IP_PLRITY_LOW ; 
 int LAPIC_LVT_MASKED ; 
 size_t LAPIC_LVT_TMR_MASK ; 
 size_t LAPIC_LVT_TMR_SHIFT ; 
 int LAPIC_LVT_TM_LEVEL ; 
 int LAPIC_LVT_VECTOR_MASK ; 
 int LAPIC_PPR_MASK ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_READ_OFFSET (int /*<<< orphan*/ ,int) ; 
 int LAPIC_SVR_ENABLE ; 
 int LAPIC_SVR_FOCUS_OFF ; 
 int LAPIC_SVR_MASK ; 
 int LAPIC_TPR_MASK ; 
 int LAPIC_VERSION_MASK ; 
 int /*<<< orphan*/  LDR ; 
 int /*<<< orphan*/  LVT_ERROR ; 
 int /*<<< orphan*/  LVT_LINT0 ; 
 int /*<<< orphan*/  LVT_LINT1 ; 
 int /*<<< orphan*/  LVT_PERFCNT ; 
 int /*<<< orphan*/  LVT_THERMAL ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 int /*<<< orphan*/  PPR ; 
 int /*<<< orphan*/  SVR ; 
 int /*<<< orphan*/  TIMER_CURRENT_COUNT ; 
 int /*<<< orphan*/  TIMER_DIVIDE_CONFIG ; 
 int /*<<< orphan*/  TIMER_INITIAL_COUNT ; 
 int /*<<< orphan*/  TMR_BASE ; 
 int /*<<< orphan*/ * TMR_str ; 
 int /*<<< orphan*/  TPR ; 
 int /*<<< orphan*/  VERSION ; 
 scalar_t__ is_x2apic ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  lapic_esr_read () ; 
 scalar_t__ lapic_vbase ; 

void
lapic_dump(void)
{
	int	i;

#define BOOL(a) ((a)?' ':'!')
#define VEC(lvt) \
	LAPIC_READ(lvt)&LAPIC_LVT_VECTOR_MASK
#define	DS(lvt)	\
	(LAPIC_READ(lvt)&LAPIC_LVT_DS_PENDING)?" SendPending" : "Idle"
#define DM(lvt) \
	DM_str[(LAPIC_READ(lvt)>>LAPIC_LVT_DM_SHIFT)&LAPIC_LVT_DM_MASK]
#define MASK(lvt) \
	BOOL(LAPIC_READ(lvt)&LAPIC_LVT_MASKED)
#define TM(lvt) \
	(LAPIC_READ(lvt)&LAPIC_LVT_TM_LEVEL)? "Level" : "Edge"
#define IP(lvt) \
	(LAPIC_READ(lvt)&LAPIC_LVT_IP_PLRITY_LOW)? "Low " : "High"

	kprintf("LAPIC %d at %p version 0x%x\n", 
		(LAPIC_READ(ID)>>LAPIC_ID_SHIFT)&LAPIC_ID_MASK,
		(void *) lapic_vbase,
		LAPIC_READ(VERSION)&LAPIC_VERSION_MASK);
	kprintf("Priorities: Task 0x%x  Arbitration 0x%x  Processor 0x%x\n",
		LAPIC_READ(TPR)&LAPIC_TPR_MASK,
		LAPIC_READ(APR)&LAPIC_APR_MASK,
		LAPIC_READ(PPR)&LAPIC_PPR_MASK);
	kprintf("Destination Format 0x%x Logical Destination 0x%x\n",
		is_x2apic ? 0 : LAPIC_READ(DFR)>>LAPIC_DFR_SHIFT,
		LAPIC_READ(LDR)>>LAPIC_LDR_SHIFT);
	kprintf("%cEnabled %cFocusChecking SV 0x%x\n",
		BOOL(LAPIC_READ(SVR)&LAPIC_SVR_ENABLE),
		BOOL(!(LAPIC_READ(SVR)&LAPIC_SVR_FOCUS_OFF)),
		LAPIC_READ(SVR) & LAPIC_SVR_MASK);
#if CONFIG_MCA
	if (mca_is_cmci_present())
		kprintf("LVT_CMCI:    Vector 0x%02x [%s] %s %cmasked\n",
			VEC(LVT_CMCI),
			DM(LVT_CMCI),
			DS(LVT_CMCI),
			MASK(LVT_CMCI));
#endif
	kprintf("LVT_TIMER:   Vector 0x%02x %s %cmasked %s\n",
		VEC(LVT_TIMER),
		DS(LVT_TIMER),
		MASK(LVT_TIMER),
		TMR_str[(LAPIC_READ(LVT_TIMER) >> LAPIC_LVT_TMR_SHIFT)
                                               &  LAPIC_LVT_TMR_MASK]);
	kprintf("  Initial Count: 0x%08x \n", LAPIC_READ(TIMER_INITIAL_COUNT));
	kprintf("  Current Count: 0x%08x \n", LAPIC_READ(TIMER_CURRENT_COUNT));
	kprintf("  Divide Config: 0x%08x \n", LAPIC_READ(TIMER_DIVIDE_CONFIG));
	kprintf("LVT_PERFCNT: Vector 0x%02x [%s] %s %cmasked\n",
		VEC(LVT_PERFCNT),
		DM(LVT_PERFCNT),
		DS(LVT_PERFCNT),
		MASK(LVT_PERFCNT));
	kprintf("LVT_THERMAL: Vector 0x%02x [%s] %s %cmasked\n",
		VEC(LVT_THERMAL),
		DM(LVT_THERMAL),
		DS(LVT_THERMAL),
		MASK(LVT_THERMAL));
	kprintf("LVT_LINT0:   Vector 0x%02x [%s][%s][%s] %s %cmasked\n",
		VEC(LVT_LINT0),
		DM(LVT_LINT0),
		TM(LVT_LINT0),
		IP(LVT_LINT0),
		DS(LVT_LINT0),
		MASK(LVT_LINT0));
	kprintf("LVT_LINT1:   Vector 0x%02x [%s][%s][%s] %s %cmasked\n",
		VEC(LVT_LINT1),
		DM(LVT_LINT1),
		TM(LVT_LINT1),
		IP(LVT_LINT1),
		DS(LVT_LINT1),
		MASK(LVT_LINT1));
	kprintf("LVT_ERROR:   Vector 0x%02x %s %cmasked\n",
		VEC(LVT_ERROR),
		DS(LVT_ERROR),
		MASK(LVT_ERROR));
	kprintf("ESR: %08x \n", lapic_esr_read());
	kprintf("       ");
	for(i=0xf; i>=0; i--)
		kprintf("%x%x%x%x",i,i,i,i);
	kprintf("\n");
	kprintf("TMR: 0x");
	for(i=7; i>=0; i--)
		kprintf("%08x",LAPIC_READ_OFFSET(TMR_BASE, i));
	kprintf("\n");
	kprintf("IRR: 0x");
	for(i=7; i>=0; i--)
		kprintf("%08x",LAPIC_READ_OFFSET(IRR_BASE, i));
	kprintf("\n");
	kprintf("ISR: 0x");
	for(i=7; i >= 0; i--)
		kprintf("%08x",LAPIC_READ_OFFSET(ISR_BASE, i));
	kprintf("\n");
}