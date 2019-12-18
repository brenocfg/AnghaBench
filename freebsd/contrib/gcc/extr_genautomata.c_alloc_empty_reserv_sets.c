#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  set_el_t ;
typedef  scalar_t__ reserv_sets_t ;

/* Variables and functions */
 int els_in_reservs ; 
 int /*<<< orphan*/  irp ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_blank (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static reserv_sets_t
alloc_empty_reserv_sets (void)
{
  reserv_sets_t result;

  obstack_blank (&irp, els_in_reservs * sizeof (set_el_t));
  result = (reserv_sets_t) obstack_base (&irp);
  (void) obstack_finish (&irp);
  memset (result, 0, els_in_reservs * sizeof (set_el_t));
  return result;
}