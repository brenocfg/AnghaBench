#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unichar ;
typedef  int rc_uint_type ;
struct TYPE_14__ {TYPE_2__* strings; } ;
typedef  TYPE_4__ rc_stringtable ;
struct TYPE_13__ {TYPE_4__* stringtable; } ;
struct TYPE_16__ {int /*<<< orphan*/  language; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ u; TYPE_6__ res_info; } ;
typedef  TYPE_5__ rc_res_resource ;
typedef  TYPE_6__ rc_res_res_info ;
struct TYPE_11__ {int id; } ;
struct TYPE_17__ {TYPE_1__ u; scalar_t__ named; } ;
typedef  TYPE_7__ rc_res_id ;
struct TYPE_12__ {int /*<<< orphan*/ * string; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ RES_TYPE_STRINGTABLE ; 
 scalar_t__ RES_TYPE_UNINITIALIZED ; 
 int /*<<< orphan*/  RT_STRING ; 
 TYPE_5__* define_standard_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  resources ; 
 int /*<<< orphan*/ * unichar_dup (int /*<<< orphan*/  const*) ; 
 scalar_t__ unichar_len (int /*<<< orphan*/  const*) ; 

void
define_stringtable (const rc_res_res_info *resinfo,
		    rc_uint_type stringid, const unichar *string)
{
  rc_res_id id;
  rc_res_resource *r;

  id.named = 0;
  id.u.id = (stringid >> 4) + 1;
  r = define_standard_resource (&resources, RT_STRING, id,
				resinfo->language, 1);

  if (r->type == RES_TYPE_UNINITIALIZED)
    {
      int i;

      r->type = RES_TYPE_STRINGTABLE;
      r->u.stringtable = ((rc_stringtable *)
			  res_alloc (sizeof (rc_stringtable)));
      for (i = 0; i < 16; i++)
	{
	  r->u.stringtable->strings[i].length = 0;
	  r->u.stringtable->strings[i].string = NULL;
	}

      r->res_info = *resinfo;
    }

  r->u.stringtable->strings[stringid & 0xf].length = unichar_len (string);
  r->u.stringtable->strings[stringid & 0xf].string = unichar_dup (string);
}