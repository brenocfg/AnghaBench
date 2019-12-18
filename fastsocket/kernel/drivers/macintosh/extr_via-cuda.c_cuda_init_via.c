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
 size_t ACR ; 
 size_t B ; 
 size_t DIRB ; 
 size_t IER ; 
 size_t IFR ; 
 size_t SR ; 
 int SR_CTRL ; 
 int SR_EXT ; 
 int SR_INT ; 
 int TACK ; 
 int TIP ; 
 int TREQ ; 
 int /*<<< orphan*/  WAIT_FOR (int,char*) ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * via ; 

__attribute__((used)) static int
cuda_init_via(void)
{
    out_8(&via[DIRB], (in_8(&via[DIRB]) | TACK | TIP) & ~TREQ);	/* TACK & TIP out */
    out_8(&via[B], in_8(&via[B]) | TACK | TIP);			/* negate them */
    out_8(&via[ACR] ,(in_8(&via[ACR]) & ~SR_CTRL) | SR_EXT);	/* SR data in */
    (void)in_8(&via[SR]);						/* clear any left-over data */
#ifdef CONFIG_PPC
    out_8(&via[IER], 0x7f);					/* disable interrupts from VIA */
    (void)in_8(&via[IER]);
#else
    out_8(&via[IER], SR_INT);					/* disable SR interrupt from VIA */
#endif

    /* delay 4ms and then clear any pending interrupt */
    mdelay(4);
    (void)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);

    /* sync with the CUDA - assert TACK without TIP */
    out_8(&via[B], in_8(&via[B]) & ~TACK);

    /* wait for the CUDA to assert TREQ in response */
    WAIT_FOR((in_8(&via[B]) & TREQ) == 0, "CUDA response to sync");

    /* wait for the interrupt and then clear it */
    WAIT_FOR(in_8(&via[IFR]) & SR_INT, "CUDA response to sync (2)");
    (void)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);

    /* finish the sync by negating TACK */
    out_8(&via[B], in_8(&via[B]) | TACK);

    /* wait for the CUDA to negate TREQ and the corresponding interrupt */
    WAIT_FOR(in_8(&via[B]) & TREQ, "CUDA response to sync (3)");
    WAIT_FOR(in_8(&via[IFR]) & SR_INT, "CUDA response to sync (4)");
    (void)in_8(&via[SR]);
    out_8(&via[IFR], SR_INT);
    out_8(&via[B], in_8(&via[B]) | TIP);	/* should be unnecessary */

    return 0;
}