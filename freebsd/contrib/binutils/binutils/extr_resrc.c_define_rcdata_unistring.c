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
typedef  int /*<<< orphan*/  unichar ;
typedef  int rc_uint_type ;
struct TYPE_6__ {int length; int /*<<< orphan*/ * w; } ;
struct TYPE_5__ {TYPE_2__ wstring; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_3__ rc_rcdata_item ;

/* Variables and functions */
 int /*<<< orphan*/  RCDATA_WSTRING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ res_alloc (int) ; 

rc_rcdata_item *
define_rcdata_unistring (const unichar *string, rc_uint_type len)
{
  rc_rcdata_item *ri;
  unichar *s;

  ri = (rc_rcdata_item *) res_alloc (sizeof (rc_rcdata_item));
  ri->next = NULL;
  ri->type = RCDATA_WSTRING;
  ri->u.wstring.length = len;
  s = (unichar *) res_alloc (len * sizeof (unichar));
  memcpy (s, string, len * sizeof (unichar));
  ri->u.wstring.w = s;

  return ri;
}