#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct uea_stats {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_2__ e1; TYPE_1__ e4; } ;
struct uea_softc {int booting; int (* send_cmvs ) (struct uea_softc*) ;scalar_t__ reset; int /*<<< orphan*/  task; int /*<<< orphan*/  work_q; scalar_t__ ovl; scalar_t__ pageno; TYPE_3__ cmv_dsc; int /*<<< orphan*/  stats; scalar_t__ cmv_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_PHY_SIG_LOST ; 
 int /*<<< orphan*/  E1_ADSLDIRECTIVE ; 
 int /*<<< orphan*/  E1_MAKEFUNCTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1_MODEMREADY ; 
 int /*<<< orphan*/  E4_ADSLDIRECTIVE ; 
 int /*<<< orphan*/  E4_MAKEFUNCTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E4_MODEMREADY ; 
 scalar_t__ EAGLE_IV ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_BOOT_IDMA ; 
 scalar_t__ UEA_CHIP_VERSION (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_END_RESET ; 
 int /*<<< orphan*/  UEA_LOOPBACK_ON ; 
 int /*<<< orphan*/  UEA_MPRX_MAILBOX ; 
 int /*<<< orphan*/  UEA_MPTX_MAILBOX ; 
 int /*<<< orphan*/  UEA_SET_2183_DATA ; 
 int /*<<< orphan*/  UEA_SET_MODE ; 
 int /*<<< orphan*/  UEA_START_RESET ; 
 int /*<<< orphan*/  UEA_SWAP_MAILBOX ; 
 int /*<<< orphan*/  UPDATE_ATM_STAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal ; 
 int stub1 (struct uea_softc*) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_request (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_vdbg (int /*<<< orphan*/ ,char*) ; 
 int uea_wait (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_cmv_ack (struct uea_softc*) ; 

__attribute__((used)) static int uea_start_reset(struct uea_softc *sc)
{
	u16 zero = 0;	/* ;-) */
	int ret;

	uea_enters(INS_TO_USBDEV(sc));
	uea_info(INS_TO_USBDEV(sc), "(re)booting started\n");

	/* mask interrupt */
	sc->booting = 1;
	/* We need to set this here because, a ack timeout could have occured,
	 * but before we start the reboot, the ack occurs and set this to 1.
	 * So we will failed to wait Ready CMV.
	 */
	sc->cmv_ack = 0;
	UPDATE_ATM_STAT(signal, ATM_PHY_SIG_LOST);

	/* reset statistics */
	memset(&sc->stats, 0, sizeof(struct uea_stats));

	/* tell the modem that we want to boot in IDMA mode */
	uea_request(sc, UEA_SET_MODE, UEA_LOOPBACK_ON, 0, NULL);
	uea_request(sc, UEA_SET_MODE, UEA_BOOT_IDMA, 0, NULL);

 	/* enter reset mode */
	uea_request(sc, UEA_SET_MODE, UEA_START_RESET, 0, NULL);

	/* original driver use 200ms, but windows driver use 100ms */
	ret = uea_wait(sc, 0, msecs_to_jiffies(100));
	if (ret < 0)
		return ret;

	/* leave reset mode */
	uea_request(sc, UEA_SET_MODE, UEA_END_RESET, 0, NULL);

	if (UEA_CHIP_VERSION(sc) != EAGLE_IV) {
 		/* clear tx and rx mailboxes */
		uea_request(sc, UEA_SET_2183_DATA, UEA_MPTX_MAILBOX, 2, &zero);
		uea_request(sc, UEA_SET_2183_DATA, UEA_MPRX_MAILBOX, 2, &zero);
		uea_request(sc, UEA_SET_2183_DATA, UEA_SWAP_MAILBOX, 2, &zero);
	}

	ret = uea_wait(sc, 0, msecs_to_jiffies(1000));
	if (ret < 0)
		return ret;

	if (UEA_CHIP_VERSION(sc) == EAGLE_IV)
		sc->cmv_dsc.e4.function = E4_MAKEFUNCTION(E4_ADSLDIRECTIVE, E4_MODEMREADY, 1);
	else
		sc->cmv_dsc.e1.function = E1_MAKEFUNCTION(E1_ADSLDIRECTIVE, E1_MODEMREADY);

	/* demask interrupt */
	sc->booting = 0;

	/* start loading DSP */
	sc->pageno = 0;
	sc->ovl = 0;
	queue_work(sc->work_q, &sc->task);

	/* wait for modem ready CMV */
	ret = wait_cmv_ack(sc);
	if (ret < 0)
		return ret;

	uea_vdbg(INS_TO_USBDEV(sc), "Ready CMV received\n");

	ret = sc->send_cmvs(sc);
	if (ret < 0)
		return ret;

	sc->reset = 0;
	uea_leaves(INS_TO_USBDEV(sc));
	return ret;
}