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
 int /*<<< orphan*/  q68_set_areg (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  q68_set_dreg (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  q68_set_pc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  q68_set_sr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  q68_set_ssp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  q68_set_usp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  yread (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m68kq68_load_state(FILE * fp)
{
   int i = 0;
   u32 val = 0;
   IOCheck_struct check = { 0, 0 };

   for (i = 0; i < 8; i++)
   {
      yread(&check, (void *)&val, sizeof(u32), 1, fp);
      q68_set_dreg(state, i, val);
   }

   for (i = 0; i < 8; i++)
   {
      yread(&check, (void *)&val, sizeof(u32), 1, fp);
      q68_set_areg(state, i, val);
   }

   yread(&check, (void *)&val, sizeof(u32), 1, fp);
   q68_set_pc(state, val);

   yread(&check, (void *)&val, sizeof(u32), 1, fp);
   q68_set_sr(state, val);

   yread(&check, (void *)&val, sizeof(u32), 1, fp);
   q68_set_usp(state, val);

   yread(&check, (void *)&val, sizeof(u32), 1, fp);
   q68_set_ssp(state, val);
}