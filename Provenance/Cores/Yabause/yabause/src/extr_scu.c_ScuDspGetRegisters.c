#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_15__ {int /*<<< orphan*/  all; } ;
struct TYPE_26__ {int /*<<< orphan*/  all; } ;
struct TYPE_24__ {int /*<<< orphan*/  all; } ;
struct TYPE_22__ {int /*<<< orphan*/  all; } ;
struct TYPE_20__ {int /*<<< orphan*/  P; } ;
struct TYPE_21__ {TYPE_2__ part; int /*<<< orphan*/  all; } ;
struct TYPE_17__ {TYPE_10__ MUL; TYPE_8__ ALU; TYPE_6__ P; TYPE_4__ AC; int /*<<< orphan*/  WA0; int /*<<< orphan*/  RA0; int /*<<< orphan*/  RY; int /*<<< orphan*/  RX; int /*<<< orphan*/  CT; int /*<<< orphan*/  DataRamReadAddress; int /*<<< orphan*/  DataRamPage; int /*<<< orphan*/  delayed; int /*<<< orphan*/  jmpaddr; int /*<<< orphan*/  LOP; int /*<<< orphan*/  TOP; int /*<<< orphan*/  PC; TYPE_3__ ProgControlPort; int /*<<< orphan*/  MD; int /*<<< orphan*/  ProgramRam; } ;
typedef  TYPE_12__ scudspregs_struct ;
struct TYPE_27__ {int /*<<< orphan*/  all; } ;
struct TYPE_25__ {int /*<<< orphan*/  all; } ;
struct TYPE_23__ {int /*<<< orphan*/  all; } ;
struct TYPE_19__ {int /*<<< orphan*/  all; } ;
struct TYPE_16__ {int /*<<< orphan*/  all; } ;
struct TYPE_18__ {TYPE_11__ MUL; TYPE_9__ ALU; TYPE_7__ P; TYPE_5__ AC; int /*<<< orphan*/  WA0; int /*<<< orphan*/  RA0; int /*<<< orphan*/  RY; int /*<<< orphan*/  RX; int /*<<< orphan*/  CT; int /*<<< orphan*/  DataRamReadAddress; int /*<<< orphan*/  DataRamPage; int /*<<< orphan*/  delayed; int /*<<< orphan*/  jmpaddr; int /*<<< orphan*/  LOP; int /*<<< orphan*/  TOP; int /*<<< orphan*/  PC; TYPE_1__ ProgControlPort; int /*<<< orphan*/  MD; int /*<<< orphan*/  ProgramRam; } ;

/* Variables and functions */
 TYPE_14__* ScuDsp ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ScuDspGetRegisters(scudspregs_struct *regs) {
   if (regs != NULL) {
      memcpy(regs->ProgramRam, ScuDsp->ProgramRam, sizeof(u32) * 256);
      memcpy(regs->MD, ScuDsp->MD, sizeof(u32) * 64 * 4);

      regs->ProgControlPort.all = ScuDsp->ProgControlPort.all;
      regs->ProgControlPort.part.P = regs->PC = ScuDsp->PC;
      regs->TOP = ScuDsp->TOP;
      regs->LOP = ScuDsp->LOP;
      regs->jmpaddr = ScuDsp->jmpaddr;
      regs->delayed = ScuDsp->delayed;
      regs->DataRamPage = ScuDsp->DataRamPage;
      regs->DataRamReadAddress = ScuDsp->DataRamReadAddress;
      memcpy(regs->CT, ScuDsp->CT, sizeof(u8) * 4);
      regs->RX = ScuDsp->RX;
      regs->RY = ScuDsp->RY;
      regs->RA0 = ScuDsp->RA0;
      regs->WA0 = ScuDsp->WA0;

      regs->AC.all = ScuDsp->AC.all;
      regs->P.all = ScuDsp->P.all;
      regs->ALU.all = ScuDsp->ALU.all;
      regs->MUL.all = ScuDsp->MUL.all;
   }
}