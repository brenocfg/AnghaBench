#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct df {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_insn_uid_debug (struct df*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
df_insn_debug (struct df *df, rtx insn, bool follow_chain, FILE *file)
{
  df_insn_uid_debug (df, INSN_UID (insn), follow_chain, file);
}