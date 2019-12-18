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
typedef  int /*<<< orphan*/  register_value_t ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  TT_LWP_WUREGS ; 
 int call_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
write_to_register_save_state (int tid, TTRACE_ARG_TYPE ss_offset, char *buf,
			      int sizeof_buf)
{
  int tt_status;
  register_value_t register_value = 0;

  tt_status = call_ttrace (TT_LWP_WUREGS,
			   tid,
			   ss_offset,
			   (TTRACE_ARG_TYPE) sizeof_buf,
			   (TTRACE_ARG_TYPE) buf);
  return tt_status;
}