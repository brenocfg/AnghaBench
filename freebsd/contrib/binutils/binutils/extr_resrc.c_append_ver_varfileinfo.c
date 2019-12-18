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
typedef  int /*<<< orphan*/  unichar ;
typedef  int /*<<< orphan*/  rc_ver_varinfo ;
struct TYPE_6__ {int /*<<< orphan*/ * var; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {TYPE_1__ var; } ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ rc_ver_info ;

/* Variables and functions */
 int /*<<< orphan*/  VERINFO_VAR ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  unichar_dup (int /*<<< orphan*/  const*) ; 

rc_ver_info *
append_ver_varfileinfo (rc_ver_info *verinfo, const unichar *key,
			rc_ver_varinfo *var)
{
  rc_ver_info *vi, **pp;

  vi = (rc_ver_info *) res_alloc (sizeof *vi);
  vi->next = NULL;
  vi->type = VERINFO_VAR;
  vi->u.var.key = unichar_dup (key);
  vi->u.var.var = var;

  for (pp = &verinfo; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = vi;

  return verinfo;
}