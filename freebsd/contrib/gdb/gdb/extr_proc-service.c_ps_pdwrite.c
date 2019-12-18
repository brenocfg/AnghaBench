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
typedef  int /*<<< orphan*/  paddr_t ;
typedef  scalar_t__ gdb_ps_write_buf_t ;
typedef  int /*<<< orphan*/  gdb_ps_size_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ps_xfer_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

ps_err_e
ps_pdwrite (gdb_ps_prochandle_t ph, paddr_t addr,
	    gdb_ps_write_buf_t buf, gdb_ps_size_t size)
{
  return ps_xfer_memory (ph, addr, (char *) buf, size, 1);
}