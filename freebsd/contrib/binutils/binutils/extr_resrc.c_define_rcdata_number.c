#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_4__ {int /*<<< orphan*/  word; } ;
struct TYPE_5__ {TYPE_1__ u; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ rc_rcdata_item ;

/* Variables and functions */
 int /*<<< orphan*/  RCDATA_DWORD ; 
 int /*<<< orphan*/  RCDATA_WORD ; 
 scalar_t__ res_alloc (int) ; 

rc_rcdata_item *
define_rcdata_number (rc_uint_type val, int dword)
{
  rc_rcdata_item *ri;

  ri = (rc_rcdata_item *) res_alloc (sizeof (rc_rcdata_item));
  ri->next = NULL;
  ri->type = dword ? RCDATA_DWORD : RCDATA_WORD;
  ri->u.word = val;

  return ri;
}