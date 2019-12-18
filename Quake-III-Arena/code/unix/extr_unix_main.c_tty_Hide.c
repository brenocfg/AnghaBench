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
struct TYPE_2__ {int cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_Back () ; 
 TYPE_1__ tty_con ; 
 scalar_t__ ttycon_hide ; 
 int /*<<< orphan*/  ttycon_on ; 

void tty_Hide()
{
  int i;
  assert(ttycon_on);
  if (ttycon_hide)
  {
    ttycon_hide++;
    return;
  }
  if (tty_con.cursor>0)
  {
    for (i=0; i<tty_con.cursor; i++)
    {
      tty_Back();
    }
  }
  ttycon_hide++;
}