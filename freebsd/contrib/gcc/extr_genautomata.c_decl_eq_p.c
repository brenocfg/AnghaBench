#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_8__ {scalar_t__ name; } ;
struct TYPE_7__ {scalar_t__ name; } ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_4__* DECL_RESERV (TYPE_1__* const) ; 
 TYPE_2__* DECL_UNIT (TYPE_1__* const) ; 
 scalar_t__ dm_reserv ; 
 scalar_t__ dm_unit ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
decl_eq_p (const void *decl_1, const void *decl_2)
{
  const decl_t d1 = (const decl_t) decl_1;
  const decl_t d2 = (const decl_t) decl_2;

  gcc_assert ((d1->mode == dm_unit && DECL_UNIT (d1)->name)
	      || (d1->mode == dm_reserv && DECL_RESERV (d1)->name));
  gcc_assert ((d2->mode == dm_unit && DECL_UNIT (d2)->name)
	      || (d2->mode == dm_reserv && DECL_RESERV (d2)->name));
  return strcmp ((d1->mode == dm_unit
                  ? DECL_UNIT (d1)->name : DECL_RESERV (d1)->name),
                 (d2->mode == dm_unit
                  ? DECL_UNIT (d2)->name : DECL_RESERV (d2)->name)) == 0;
}