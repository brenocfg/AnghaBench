#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  init_vx_ops () ; 
 int /*<<< orphan*/  init_vx_run_ops () ; 
 TYPE_1__ rpcTimeout ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_uinteger ; 
 int /*<<< orphan*/  vx_ops ; 
 int /*<<< orphan*/  vx_run_ops ; 

void
_initialize_vx (void)
{
  init_vx_ops ();
  add_target (&vx_ops);
  init_vx_run_ops ();
  add_target (&vx_run_ops);

  add_show_from_set
    (add_set_cmd ("vxworks-timeout", class_support, var_uinteger,
		  (char *) &rpcTimeout.tv_sec,
		  "Set seconds to wait for rpc calls to return.\n\
Set the number of seconds to wait for rpc calls to return.", &setlist),
     &showlist);
}