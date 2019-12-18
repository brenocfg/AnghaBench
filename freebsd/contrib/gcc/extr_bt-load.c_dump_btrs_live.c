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

/* Variables and functions */
 int /*<<< orphan*/ * btrs_live ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  dump_hard_reg_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
dump_btrs_live (int bb)
{
  fprintf (dump_file, "BB%d live:", bb);
  dump_hard_reg_set (btrs_live[bb]);
  fprintf (dump_file, "\n");
}