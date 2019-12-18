#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ window; int /*<<< orphan*/  mouseExit; int /*<<< orphan*/  mouseExitText; } ;
typedef  TYPE_2__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_RunScript (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int WINDOW_LB_LEFTARROW ; 
 int WINDOW_LB_RIGHTARROW ; 
 int WINDOW_MOUSEOVERTEXT ; 

void Item_MouseLeave(itemDef_t *item) {
  if (item) {
    if (item->window.flags & WINDOW_MOUSEOVERTEXT) {
      Item_RunScript(item, item->mouseExitText);
      item->window.flags &= ~WINDOW_MOUSEOVERTEXT;
    }
    Item_RunScript(item, item->mouseExit);
    item->window.flags &= ~(WINDOW_LB_RIGHTARROW | WINDOW_LB_LEFTARROW);
  }
}