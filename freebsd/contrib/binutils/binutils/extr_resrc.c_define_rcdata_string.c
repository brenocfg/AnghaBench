#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int rc_uint_type ;
struct TYPE_5__ {int length; char* s; } ;
struct TYPE_6__ {TYPE_1__ string; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_3__ rc_rcdata_item ;

/* Variables and functions */
 int /*<<< orphan*/  RCDATA_STRING ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ res_alloc (int) ; 

rc_rcdata_item *
define_rcdata_string (const char *string, rc_uint_type len)
{
  rc_rcdata_item *ri;
  char *s;

  ri = (rc_rcdata_item *) res_alloc (sizeof (rc_rcdata_item));
  ri->next = NULL;
  ri->type = RCDATA_STRING;
  ri->u.string.length = len;
  s = (char *) res_alloc (len);
  memcpy (s, string, len);
  ri->u.string.s = s;

  return ri;
}