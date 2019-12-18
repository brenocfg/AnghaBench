#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdp2Internal_struct ;
typedef  int /*<<< orphan*/  Vdp2 ;
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ Vdp2ColorRam ; 
 int /*<<< orphan*/  Vdp2Internal ; 
 scalar_t__ Vdp2Ram ; 
 scalar_t__ Vdp2Regs ; 
 int /*<<< orphan*/  ywrite (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

int Vdp2SaveState(FILE *fp)
{
   int offset;
   IOCheck_struct check = { 0, 0 };

   offset = StateWriteHeader(fp, "VDP2", 1);

   // Write registers
   ywrite(&check, (void *)Vdp2Regs, sizeof(Vdp2), 1, fp);

   // Write VDP2 ram
   ywrite(&check, (void *)Vdp2Ram, 0x80000, 1, fp);

   // Write CRAM
   ywrite(&check, (void *)Vdp2ColorRam, 0x1000, 1, fp);

   // Write internal variables
   ywrite(&check, (void *)&Vdp2Internal, sizeof(Vdp2Internal_struct), 1, fp);

   return StateFinishHeader(fp, offset);
}