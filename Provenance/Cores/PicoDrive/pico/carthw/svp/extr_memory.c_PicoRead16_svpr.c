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
struct TYPE_5__ {TYPE_1__* gr; } ;
struct TYPE_6__ {TYPE_2__ ssp1601; } ;
struct TYPE_4__ {int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int PicoRead16_io (int) ; 
 size_t SSP_PM0 ; 
 size_t SSP_XST ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  realsize ; 
 TYPE_3__* svp ; 

__attribute__((used)) static u32 PicoRead16_svpr(u32 a)
{
  u32 d = 0;

  // regs
  if ((a & ~0x0f) == 0xa15000) {
    switch (a & 0xf) {
      case 0:
      case 2:
        d = svp->ssp1601.gr[SSP_XST].h;
        break;

      case 4:
        d = svp->ssp1601.gr[SSP_PM0].h;
        svp->ssp1601.gr[SSP_PM0].h &= ~1;
	break;
    }

#if EL_LOGMASK & EL_SVP
    {
      static int a15004_looping = 0;
      if (a == 0xa15004 && (d & 1))
        a15004_looping = 0;

      if (!a15004_looping)
        elprintf(EL_SVP, "SVP r%i: [%06x] %04x @%06x", realsize, a, d, SekPc);

      if (a == 0xa15004 && !(d&1)) {
        if (!a15004_looping)
          elprintf(EL_SVP, "SVP det TIGHT loop: a15004");
        a15004_looping = 1;
      }
      else
        a15004_looping = 0;
    }
#endif
    return d;
  }

  //if (a == 0x30fe02 && d == 0)
  //  elprintf(EL_ANOMALY, "SVP lag?");

  return PicoRead16_io(a);
}