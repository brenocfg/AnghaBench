#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_8__ {TYPE_1__* next_bb; } ;
struct TYPE_7__ {struct TYPE_7__* next_bb; } ;

/* Variables and functions */
 TYPE_1__* EXIT_BLOCK_PTR ; 
 TYPE_3__* single_succ (TYPE_1__*) ; 
 scalar_t__ single_succ_p (TYPE_1__*) ; 

__attribute__((used)) static bool
last_basic_block_p (basic_block bb)
{
  if (bb == EXIT_BLOCK_PTR)
    return false;

  return (bb->next_bb == EXIT_BLOCK_PTR
	  || (bb->next_bb->next_bb == EXIT_BLOCK_PTR
	      && single_succ_p (bb)
	      && single_succ (bb)->next_bb == EXIT_BLOCK_PTR));
}