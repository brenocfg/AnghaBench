#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__ id; } ;
typedef  TYPE_3__ rc_toolbar_item ;
struct TYPE_9__ {TYPE_3__* items; } ;
typedef  TYPE_4__ rc_toolbar ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
write_rc_toolbar (FILE *e, const rc_toolbar *tb)
{
  rc_toolbar_item *it;
  indent (e, 0);
  fprintf (e, "BEGIN\n");
  it = tb->items;
  while(it != NULL)
  {
    indent (e, 2);
    if (it->id.u.id == 0)
      fprintf (e, "SEPARATOR\n");
    else 
      fprintf (e, "BUTTON %d\n", (int) it->id.u.id);
    it = it->next;
  }
  indent (e, 0);
  fprintf (e, "END\n");
}