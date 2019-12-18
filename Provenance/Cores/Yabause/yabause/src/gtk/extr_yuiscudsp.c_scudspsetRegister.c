#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int value ;
typedef  int u32 ;
struct TYPE_14__ {int H; int L; } ;
struct TYPE_15__ {TYPE_5__ part; } ;
struct TYPE_12__ {int H; int L; } ;
struct TYPE_13__ {TYPE_3__ part; } ;
struct TYPE_10__ {int PR; int EP; int T0; int S; int Z; int C; int V; int E; int ES; int EX; int LE; int P; } ;
struct TYPE_11__ {TYPE_1__ part; } ;
struct TYPE_16__ {int TOP; int LOP; int* CT; int RA0; int WA0; int RX; int RY; TYPE_6__ AC; TYPE_4__ P; TYPE_2__ ProgControlPort; } ;
typedef  TYPE_7__ scudspregs_struct ;
typedef  int /*<<< orphan*/  YuiScudsp ;

/* Variables and functions */
 int /*<<< orphan*/  ScuDspGetRegisters (TYPE_7__*) ; 
 int /*<<< orphan*/  ScuDspSetRegisters (TYPE_7__*) ; 

__attribute__((used)) static void scudspsetRegister( YuiScudsp *scudsp, int nReg, u32 value ) {
  /* set register number <nReg> to value <value> in proc <scudsp> */

  scudspregs_struct scudspregs;
  ScuDspGetRegisters(&scudspregs);

  switch ( nReg ) {
  case 0: scudspregs.ProgControlPort.part.PR = value; break;
  case 1: scudspregs.ProgControlPort.part.EP = value; break;
  case 2: scudspregs.ProgControlPort.part.T0 = value; break;
  case 3: scudspregs.ProgControlPort.part.S = value; break;
  case 4: scudspregs.ProgControlPort.part.Z = value; break;
  case 5: scudspregs.ProgControlPort.part.C = value; break;
  case 6: scudspregs.ProgControlPort.part.V = value; break;
  case 7: scudspregs.ProgControlPort.part.E = value; break;
  case 8: scudspregs.ProgControlPort.part.ES = value; break;
  case 9: scudspregs.ProgControlPort.part.EX = value; break;
  case 10: scudspregs.ProgControlPort.part.LE = value; break;
  case 11: scudspregs.ProgControlPort.part.P = value; break;
  case 12: scudspregs.TOP = value; break;
  case 13: scudspregs.LOP = value; break;
  case 14: 
    scudspregs.CT[0] = (value>>24) & 0xff;
    scudspregs.CT[1] = (value>>16) & 0xff;
    scudspregs.CT[2] = (value>>8) & 0xff;
    scudspregs.CT[3] = (value) & 0xff;
    break;
  case 15: scudspregs.RA0 = value; break;
  case 16: scudspregs.WA0 = value; break;
  case 17: scudspregs.RX = value; break;
  case 18: scudspregs.RY = value; break;
  case 19: scudspregs.P.part.H = value; break;
  case 20: scudspregs.P.part.L = value; break;
  case 21: scudspregs.AC.part.H = value; break;
  case 22: scudspregs.AC.part.L = value; break;
  }

  ScuDspSetRegisters(&scudspregs);
}