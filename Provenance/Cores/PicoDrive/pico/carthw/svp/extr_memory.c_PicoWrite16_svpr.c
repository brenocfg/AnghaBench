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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  emu_status; TYPE_2__* gr; } ;
struct TYPE_6__ {TYPE_1__ ssp1601; } ;
struct TYPE_5__ {int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int /*<<< orphan*/  PicoWrite16_io (int,int) ; 
 size_t SSP_PM0 ; 
 int /*<<< orphan*/  SSP_WAIT_PM0 ; 
 size_t SSP_XST ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* svp ; 

__attribute__((used)) static void PicoWrite16_svpr(u32 a, u32 d)
{
  elprintf(EL_SVP, "SVP w16: [%06x] %04x @%06x", a, d, SekPc);

  if ((a & ~0x0f) == 0xa15000) {
    if (a == 0xa15000 || a == 0xa15002) {
      // just guessing here
      svp->ssp1601.gr[SSP_XST].h = d;
      svp->ssp1601.gr[SSP_PM0].h |= 2;
      svp->ssp1601.emu_status &= ~SSP_WAIT_PM0;
    }
    //else if (a == 0xa15006) svp->ssp1601.gr[SSP_PM0].h = d | (d << 1);
    // 0xa15006 probably has 'halt'
    return;
  }

  PicoWrite16_io(a, d);
}