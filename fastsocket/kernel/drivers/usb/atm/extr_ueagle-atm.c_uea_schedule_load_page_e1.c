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
struct uea_softc {int ovl; int /*<<< orphan*/  task; int /*<<< orphan*/  work_q; int /*<<< orphan*/  pageno; } ;
struct intr_pkt {int e1_bOvl; int /*<<< orphan*/  e1_bSwapPageNo; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uea_schedule_load_page_e1(struct uea_softc *sc, struct intr_pkt *intr)
{
	sc->pageno = intr->e1_bSwapPageNo;
	sc->ovl = intr->e1_bOvl >> 4 | intr->e1_bOvl << 4;
	queue_work(sc->work_q, &sc->task);
}