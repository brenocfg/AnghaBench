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
struct TYPE_16__ {int /*<<< orphan*/  all; } ;
struct TYPE_27__ {int /*<<< orphan*/  all; } ;
struct TYPE_25__ {int /*<<< orphan*/  all; } ;
struct TYPE_23__ {int /*<<< orphan*/  all; } ;
struct TYPE_20__ {int /*<<< orphan*/  P; } ;
struct TYPE_21__ {TYPE_2__ part; int /*<<< orphan*/  all; } ;
struct TYPE_17__ {TYPE_11__ MUL; TYPE_9__ ALU; TYPE_7__ P; TYPE_5__ AC; int /*<<< orphan*/  WA0; int /*<<< orphan*/  RA0; int /*<<< orphan*/  RY; int /*<<< orphan*/  RX; int /*<<< orphan*/  CT; int /*<<< orphan*/  DataRamReadAddress; int /*<<< orphan*/  DataRamPage; int /*<<< orphan*/  delayed; int /*<<< orphan*/  jmpaddr; int /*<<< orphan*/  LOP; int /*<<< orphan*/  TOP; TYPE_3__ ProgControlPort; int /*<<< orphan*/  MD; int /*<<< orphan*/  ProgramRam; } ;
typedef  TYPE_12__ scudspregs_struct ;
struct TYPE_26__ {int /*<<< orphan*/  all; } ;
struct TYPE_24__ {int /*<<< orphan*/  all; } ;
struct TYPE_22__ {int /*<<< orphan*/  all; } ;
struct TYPE_19__ {int /*<<< orphan*/  all; } ;
struct TYPE_15__ {int /*<<< orphan*/  all; } ;
struct TYPE_18__ {TYPE_10__ MUL; TYPE_8__ ALU; TYPE_6__ P; TYPE_4__ AC; int /*<<< orphan*/  WA0; int /*<<< orphan*/  RA0; int /*<<< orphan*/  RY; int /*<<< orphan*/  RX; int /*<<< orphan*/  CT; int /*<<< orphan*/  DataRamReadAddress; int /*<<< orphan*/  DataRamPage; int /*<<< orphan*/  delayed; int /*<<< orphan*/  jmpaddr; int /*<<< orphan*/  LOP; int /*<<< orphan*/  TOP; int /*<<< orphan*/  PC; TYPE_1__ ProgControlPort; int /*<<< orphan*/  MD; int /*<<< orphan*/  ProgramRam; } ;

/* Variables and functions */
 TYPE_14__* ScuDsp ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ScuDspSetRegisters(scudspregs_struct *regs) {
   if (regs != NULL) {
      memcpy(ScuDsp->ProgramRam, regs->ProgramRam, sizeof(u32) * 256);
      memcpy(ScuDsp->MD, regs->MD, sizeof(u32) * 64 * 4);

      ScuDsp->ProgControlPort.all = regs->ProgControlPort.all;
      ScuDsp->PC = regs->ProgControlPort.part.P;
      ScuDsp->TOP = regs->TOP;
      ScuDsp->LOP = regs->LOP;
      ScuDsp->jmpaddr = regs->jmpaddr;
      ScuDsp->delayed = regs->delayed;
      ScuDsp->DataRamPage = regs->DataRamPage;
      ScuDsp->DataRamReadAddress = regs->DataRamReadAddress;
      memcpy(ScuDsp->CT, regs->CT, sizeof(u8) * 4);
      ScuDsp->RX = regs->RX;
      ScuDsp->RY = regs->RY;
      ScuDsp->RA0 = regs->RA0;
      ScuDsp->WA0 = regs->WA0;

      ScuDsp->AC.all = regs->AC.all;
      ScuDsp->P.all = regs->P.all;
      ScuDsp->ALU.all = regs->ALU.all;
      ScuDsp->MUL.all = regs->MUL.all;
   }
}