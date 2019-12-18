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
typedef  TYPE_1__* btr_user ;
struct TYPE_3__ {int other_use_this_block; scalar_t__ use; struct TYPE_3__* next; } ;

/* Variables and functions */
 unsigned int REGNO (scalar_t__) ; 

__attribute__((used)) static void
note_other_use_this_block (unsigned int regno, btr_user users_this_bb)
{
  btr_user user;

  for (user = users_this_bb; user != NULL; user = user->next)
    if (user->use && REGNO (user->use) == regno)
      user->other_use_this_block = 1;
}