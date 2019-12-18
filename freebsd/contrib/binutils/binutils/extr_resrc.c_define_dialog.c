#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  language; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dialog; } ;
struct TYPE_7__ {TYPE_3__ res_info; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ rc_res_resource ;
typedef  TYPE_3__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_dialog ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_DIALOG ; 
 int /*<<< orphan*/  RT_DIALOG ; 
 TYPE_2__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 

void
define_dialog (rc_res_id id, const rc_res_res_info *resinfo,
	       const rc_dialog *dialog)
{
  rc_dialog *copy;
  rc_res_resource *r;

  copy = (rc_dialog *) res_alloc (sizeof *copy);
  *copy = *dialog;

  r = define_standard_resource (&resources, RT_DIALOG, id,
				resinfo->language, 0);
  r->type = RES_TYPE_DIALOG;
  r->u.dialog = copy;
  r->res_info = *resinfo;
}