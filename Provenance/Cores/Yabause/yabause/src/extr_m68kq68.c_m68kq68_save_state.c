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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ q68_get_areg (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ q68_get_dreg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ q68_get_pc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ q68_get_sr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ q68_get_ssp (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ q68_get_usp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  ywrite (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m68kq68_save_state(FILE * fp)
{
   int i = 0;
   u32 val = 0;
   IOCheck_struct check = { 0, 0 };

   for (i = 0; i < 8; i++)
   {
      val = q68_get_dreg(state, i);
      ywrite(&check, (void *)&val, sizeof(u32), 1, fp);
   }

   for (i = 0; i < 8; i++)
   {
      val = q68_get_areg(state, i, val);
      ywrite(&check, (void *)&val, sizeof(u32), 1, fp);
   }

   val = q68_get_pc(state, val);
   ywrite(&check, (void *)&val, sizeof(u32), 1, fp);

   val = q68_get_sr(state, val);
   ywrite(&check, (void *)&val, sizeof(u32), 1, fp);

   val = q68_get_usp(state, val);
   ywrite(&check, (void *)&val, sizeof(u32), 1, fp);

   val = q68_get_ssp(state, val);
   ywrite(&check, (void *)&val, sizeof(u32), 1, fp);
}