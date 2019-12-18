#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unw_record_type ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_1__ r; int /*<<< orphan*/  slot_number; } ;
typedef  TYPE_2__ unw_rec_list ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT_NUM_NOT_SET ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* xmalloc (int) ; 

__attribute__((used)) static unw_rec_list *
alloc_record (unw_record_type t)
{
  unw_rec_list *ptr;
  ptr = xmalloc (sizeof (*ptr));
  memset (ptr, 0, sizeof (*ptr));
  ptr->slot_number = SLOT_NUM_NOT_SET;
  ptr->r.type = t;
  return ptr;
}