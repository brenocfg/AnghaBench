#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int LMC_CSR_READ (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LMC_MII_SYNC (TYPE_1__* const) ; 
 int /*<<< orphan*/  csr_9 ; 
 int /*<<< orphan*/  lmc_delay () ; 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 

unsigned lmc_mii_readreg (lmc_softc_t * const sc, unsigned devaddr, unsigned regno) /*fold00*/
{
    int i;
    int command = (0xf6 << 10) | (devaddr << 5) | regno;
    int retval = 0;

    lmc_trace(sc->lmc_device, "lmc_mii_readreg in");

    LMC_MII_SYNC (sc);

    lmc_trace(sc->lmc_device, "lmc_mii_readreg: done sync");

    for (i = 15; i >= 0; i--)
    {
        int dataval = (command & (1 << i)) ? 0x20000 : 0;

        LMC_CSR_WRITE (sc, csr_9, dataval);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        LMC_CSR_WRITE (sc, csr_9, dataval | 0x10000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
    }

    lmc_trace(sc->lmc_device, "lmc_mii_readreg: done1");

    for (i = 19; i > 0; i--)
    {
        LMC_CSR_WRITE (sc, csr_9, 0x40000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
        retval = (retval << 1) | ((LMC_CSR_READ (sc, csr_9) & 0x80000) ? 1 : 0);
        LMC_CSR_WRITE (sc, csr_9, 0x40000 | 0x10000);
        lmc_delay ();
        /* __SLOW_DOWN_IO; */
    }

    lmc_trace(sc->lmc_device, "lmc_mii_readreg out");

    return (retval >> 1) & 0xffff;
}