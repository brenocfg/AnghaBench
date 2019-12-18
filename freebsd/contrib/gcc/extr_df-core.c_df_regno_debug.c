#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct df {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_chain; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_2__* DF_REG_DEF_GET (struct df*,unsigned int) ; 
 TYPE_1__* DF_REG_USE_GET (struct df*,unsigned int) ; 
 int /*<<< orphan*/  df_regs_chain_dump (struct df*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
df_regno_debug (struct df *df, unsigned int regno, FILE *file)
{
  fprintf (file, "reg %d defs ", regno);
  df_regs_chain_dump (df, DF_REG_DEF_GET (df, regno)->reg_chain, file);
  fprintf (file, " uses ");
  df_regs_chain_dump (df, DF_REG_USE_GET (df, regno)->reg_chain, file);
  fprintf (file, "\n");
}