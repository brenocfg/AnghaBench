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
struct TYPE_7__ {unsigned long ecount; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_2__ record; } ;
struct TYPE_10__ {TYPE_3__ r; } ;
typedef  TYPE_4__ unw_rec_list ;

/* Variables and functions */
 TYPE_4__* alloc_record (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epilogue ; 

__attribute__((used)) static unw_rec_list *
output_epilogue (unsigned long ecount)
{
  unw_rec_list *ptr = alloc_record (epilogue);
  ptr->r.record.b.ecount = ecount;
  return ptr;
}