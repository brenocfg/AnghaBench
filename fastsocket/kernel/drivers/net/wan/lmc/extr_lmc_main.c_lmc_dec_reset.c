#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int lmc_intrmask; int lmc_busmode; int lmc_cmdmode; int /*<<< orphan*/  lmc_device; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 void* LMC_CSR_READ (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int TULIP_BUSMODE_SWRESET ; 
 int TULIP_CMD_FULLDUPLEX ; 
 int TULIP_CMD_MUSTBEONE ; 
 int TULIP_CMD_NOHEARTBEAT ; 
 int TULIP_CMD_OPERMODE ; 
 int TULIP_CMD_PASSBADPKT ; 
 int TULIP_CMD_PORTSELECT ; 
 int TULIP_CMD_PROMISCUOUS ; 
 int TULIP_CMD_RECEIVEALL ; 
 int TULIP_CMD_STOREFWD ; 
 int TULIP_CMD_THRESHOLDCTL ; 
 int TULIP_CMD_TXTHRSHLDCTL ; 
 int TULIP_WATCHDOG_RXDISABLE ; 
 int TULIP_WATCHDOG_TXDISABLE ; 
 int /*<<< orphan*/  csr_busmode ; 
 int /*<<< orphan*/  csr_command ; 
 int /*<<< orphan*/  csr_intr ; 
 int /*<<< orphan*/  csr_sia_general ; 
 int /*<<< orphan*/  lmc_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lmc_dec_reset(lmc_softc_t * const sc) /*fold00*/
{
    u32 val;
    lmc_trace(sc->lmc_device, "lmc_dec_reset in");

    /*
     * disable all interrupts
     */
    sc->lmc_intrmask = 0;
    LMC_CSR_WRITE(sc, csr_intr, sc->lmc_intrmask);

    /*
     * Reset the chip with a software reset command.
     * Wait 10 microseconds (actually 50 PCI cycles but at
     * 33MHz that comes to two microseconds but wait a
     * bit longer anyways)
     */
    LMC_CSR_WRITE(sc, csr_busmode, TULIP_BUSMODE_SWRESET);
    udelay(25);
#ifdef __sparc__
    sc->lmc_busmode = LMC_CSR_READ(sc, csr_busmode);
    sc->lmc_busmode = 0x00100000;
    sc->lmc_busmode &= ~TULIP_BUSMODE_SWRESET;
    LMC_CSR_WRITE(sc, csr_busmode, sc->lmc_busmode);
#endif
    sc->lmc_cmdmode = LMC_CSR_READ(sc, csr_command);

    /*
     * We want:
     *   no ethernet address in frames we write
     *   disable padding (txdesc, padding disable)
     *   ignore runt frames (rdes0 bit 15)
     *   no receiver watchdog or transmitter jabber timer
     *       (csr15 bit 0,14 == 1)
     *   if using 16-bit CRC, turn off CRC (trans desc, crc disable)
     */

    sc->lmc_cmdmode |= ( TULIP_CMD_PROMISCUOUS
                         | TULIP_CMD_FULLDUPLEX
                         | TULIP_CMD_PASSBADPKT
                         | TULIP_CMD_NOHEARTBEAT
                         | TULIP_CMD_PORTSELECT
                         | TULIP_CMD_RECEIVEALL
                         | TULIP_CMD_MUSTBEONE
                       );
    sc->lmc_cmdmode &= ~( TULIP_CMD_OPERMODE
                          | TULIP_CMD_THRESHOLDCTL
                          | TULIP_CMD_STOREFWD
                          | TULIP_CMD_TXTHRSHLDCTL
                        );

    LMC_CSR_WRITE(sc, csr_command, sc->lmc_cmdmode);

    /*
     * disable receiver watchdog and transmit jabber
     */
    val = LMC_CSR_READ(sc, csr_sia_general);
    val |= (TULIP_WATCHDOG_TXDISABLE | TULIP_WATCHDOG_RXDISABLE);
    LMC_CSR_WRITE(sc, csr_sia_general, val);

    lmc_trace(sc->lmc_device, "lmc_dec_reset out");
}