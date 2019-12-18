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
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_OK ; 

ps_err_e
ps_pstop (gdb_ps_prochandle_t ph)
{
  /* The process is always stopped when under control of GDB.  */
  return PS_OK;
}