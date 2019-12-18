#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_10__ {int /*<<< orphan*/  language; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
struct TYPE_9__ {TYPE_4__ res_info; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ rc_res_resource ;
typedef  TYPE_4__ rc_res_res_info ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_rcdata_item ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_ICON ; 
 int /*<<< orphan*/  RT_ICON ; 
 TYPE_3__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rcdata_render_as_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resources ; 

__attribute__((used)) static void
define_icon_rcdata (rc_res_id id, const rc_res_res_info *resinfo,
		    rc_rcdata_item *data)
{
  rc_res_resource *r;
  rc_uint_type len_data;
  bfd_byte *pb_data;

  pb_data = rcdata_render_as_buffer (data, &len_data);

  r = define_standard_resource (&resources, RT_ICON, id, resinfo->language, 0);
  r->type = RES_TYPE_ICON;
  r->u.data.length = len_data;
  r->u.data.data = pb_data;
  r->res_info = *resinfo;
}