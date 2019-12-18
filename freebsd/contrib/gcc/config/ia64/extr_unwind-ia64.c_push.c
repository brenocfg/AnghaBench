#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct unw_reg_state* next; } ;
struct unw_state_record {TYPE_1__ curr; } ;
struct unw_reg_state {int dummy; } ;

/* Variables and functions */
 struct unw_reg_state* alloc_reg_state () ; 
 int /*<<< orphan*/  memcpy (struct unw_reg_state*,TYPE_1__*,int) ; 

__attribute__((used)) static void
push (struct unw_state_record *sr)
{
  struct unw_reg_state *rs = alloc_reg_state ();
  memcpy (rs, &sr->curr, sizeof (*rs));
  sr->curr.next = rs;
}