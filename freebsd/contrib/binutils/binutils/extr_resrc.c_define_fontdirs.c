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
struct TYPE_8__ {int /*<<< orphan*/  fontdir; } ;
struct TYPE_9__ {int /*<<< orphan*/  res_info; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ rc_res_resource ;
struct TYPE_7__ {int id; } ;
struct TYPE_10__ {TYPE_1__ u; scalar_t__ named; } ;
typedef  TYPE_4__ rc_res_id ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_FONTDIR ; 
 int /*<<< orphan*/  RT_FONTDIR ; 
 TYPE_3__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fontdirs ; 
 int /*<<< orphan*/  fontdirs_resinfo ; 
 int /*<<< orphan*/  resources ; 

__attribute__((used)) static void
define_fontdirs (void)
{
  rc_res_resource *r;
  rc_res_id id;

  id.named = 0;
  id.u.id = 1;

  r = define_standard_resource (&resources, RT_FONTDIR, id, 0x409, 0);

  r->type = RES_TYPE_FONTDIR;
  r->u.fontdir = fontdirs;
  r->res_info = fontdirs_resinfo;
}