#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * var; int /*<<< orphan*/ * fixed; } ;
typedef  TYPE_3__ rc_versioninfo ;
typedef  int /*<<< orphan*/  rc_ver_info ;
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_6__ {int /*<<< orphan*/  language; } ;
struct TYPE_7__ {TYPE_3__* versioninfo; } ;
struct TYPE_9__ {TYPE_1__ res_info; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ rc_res_resource ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_fixed_versioninfo ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_VERSIONINFO ; 
 int /*<<< orphan*/  RT_VERSION ; 
 TYPE_4__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 

void
define_versioninfo (rc_res_id id, rc_uint_type language,
		    rc_fixed_versioninfo *fixedverinfo,
		    rc_ver_info *verinfo)
{
  rc_res_resource *r;

  r = define_standard_resource (&resources, RT_VERSION, id, language, 0);
  r->type = RES_TYPE_VERSIONINFO;
  r->u.versioninfo = ((rc_versioninfo *)
		      res_alloc (sizeof (rc_versioninfo)));
  r->u.versioninfo->fixed = fixedverinfo;
  r->u.versioninfo->var = verinfo;
  r->res_info.language = language;
}