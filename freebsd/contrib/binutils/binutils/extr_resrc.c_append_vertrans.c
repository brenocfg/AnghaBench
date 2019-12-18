#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; void* charset; void* language; } ;
typedef  TYPE_1__ rc_ver_varinfo ;
typedef  void* rc_uint_type ;

/* Variables and functions */
 scalar_t__ res_alloc (int) ; 

rc_ver_varinfo *
append_vertrans (rc_ver_varinfo *var, rc_uint_type language,
		 rc_uint_type charset)
{
  rc_ver_varinfo *vv, **pp;

  vv = (rc_ver_varinfo *) res_alloc (sizeof (rc_ver_varinfo));
  vv->next = NULL;
  vv->language = language;
  vv->charset = charset;

  for (pp = &var; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = vv;

  return var;
}