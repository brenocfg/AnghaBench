#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int /*<<< orphan*/  dirty1; int /*<<< orphan*/  CycleSup; int /*<<< orphan*/  CycleIO; int /*<<< orphan*/  CycleToDo; int /*<<< orphan*/  IRQLine; int /*<<< orphan*/  Status; int /*<<< orphan*/  USP; int /*<<< orphan*/  flag_S; int /*<<< orphan*/  flag_I; int /*<<< orphan*/  flag_X; int /*<<< orphan*/  flag_N; int /*<<< orphan*/  flag_notZ; int /*<<< orphan*/  flag_V; int /*<<< orphan*/  flag_C; int /*<<< orphan*/ * A; int /*<<< orphan*/ * D; } ;
typedef  TYPE_1__ c68k_struc ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  C68K ; 
 scalar_t__ C68k_Get_PC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ywrite (TYPE_2__*,void*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void C68k_Save_State(c68k_struc *mcpu, FILE * fp)
{
   IOCheck_struct check = { 0, 0 };
   int i = 0;
   u32 pc = 0;

   for (i = 0; i < 8; i++)
      ywrite(&check, (void *)&mcpu->D[i], sizeof(u32), 1, fp);

   for (i = 0; i < 8; i++)
      ywrite(&check, (void *)&mcpu->A[i], sizeof(u32), 1, fp);

   ywrite(&check, (void *)&mcpu->flag_C, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->flag_V, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->flag_notZ, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->flag_N, sizeof(u32), 1, fp);

   ywrite(&check, (void *)&mcpu->flag_X, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->flag_I, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->flag_S, sizeof(u32), 1, fp);

   ywrite(&check, (void *)&mcpu->USP, sizeof(u32), 1, fp);

   pc = C68k_Get_PC(&C68K);

   ywrite(&check, (void *)&pc, sizeof(u32), 1, fp);

   ywrite(&check, (void *)&mcpu->Status, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&mcpu->IRQLine, sizeof(s32), 1, fp);

   ywrite(&check, (void *)&mcpu->CycleToDo, sizeof(s32), 1, fp);
   ywrite(&check, (void *)&mcpu->CycleIO, sizeof(s32), 1, fp);
   ywrite(&check, (void *)&mcpu->CycleSup, sizeof(s32), 1, fp);
   ywrite(&check, (void *)&mcpu->dirty1, sizeof(u32), 1, fp);
}