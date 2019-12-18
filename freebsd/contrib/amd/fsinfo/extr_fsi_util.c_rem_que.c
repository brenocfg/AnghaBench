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
struct TYPE_3__ {struct TYPE_3__* q_back; struct TYPE_3__* q_forw; } ;
typedef  TYPE_1__ qelem ;

/* Variables and functions */

void
rem_que(qelem *elem)
{
  qelem *p, *p2;

  p = elem->q_forw;
  p2 = elem->q_back;

  p2->q_forw = p;
  p->q_back = p2;
}