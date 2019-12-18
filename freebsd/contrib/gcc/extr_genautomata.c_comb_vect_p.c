#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_ainsn_table_t ;
struct TYPE_3__ {int /*<<< orphan*/  comb_vect; int /*<<< orphan*/  full_vect; } ;

/* Variables and functions */
 int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_el_t ; 

__attribute__((used)) static int
comb_vect_p (state_ainsn_table_t tab)
{
  return  (2 * VEC_length (vect_el_t, tab->full_vect)
           > 5 * VEC_length (vect_el_t, tab->comb_vect));
}