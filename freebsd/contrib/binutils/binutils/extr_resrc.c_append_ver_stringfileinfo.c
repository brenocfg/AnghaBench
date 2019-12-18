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
typedef  int /*<<< orphan*/  rc_ver_stringinfo ;
struct TYPE_6__ {int /*<<< orphan*/ * strings; int /*<<< orphan*/  language; } ;
struct TYPE_7__ {TYPE_1__ string; } ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ rc_ver_info ;
typedef  int /*<<< orphan*/  rc_uint_type ;

/* Variables and functions */
 int /*<<< orphan*/  VERINFO_STRING ; 
 scalar_t__ res_alloc (int) ; 
 int /*<<< orphan*/  unicode_from_ascii (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

rc_ver_info *
append_ver_stringfileinfo (rc_ver_info *verinfo, const char *language,
			   rc_ver_stringinfo *strings)
{
  rc_ver_info *vi, **pp;

  vi = (rc_ver_info *) res_alloc (sizeof (rc_ver_info));
  vi->next = NULL;
  vi->type = VERINFO_STRING;
  unicode_from_ascii ((rc_uint_type *) NULL, &vi->u.string.language, language);
  vi->u.string.strings = strings;

  for (pp = &verinfo; *pp != NULL; pp = &(*pp)->next)
    ;
  *pp = vi;

  return verinfo;
}