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
struct undo {struct undo* next; } ;
struct TYPE_2__ {struct undo* undos; struct undo* frees; } ;

/* Variables and functions */
 TYPE_1__ undobuf ; 

__attribute__((used)) static void
undo_commit (void)
{
  struct undo *undo, *next;

  for (undo = undobuf.undos; undo; undo = next)
    {
      next = undo->next;
      undo->next = undobuf.frees;
      undobuf.frees = undo;
    }
  undobuf.undos = 0;
}