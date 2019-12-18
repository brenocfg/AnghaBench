#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qelem {TYPE_2__* q_forw; TYPE_1__* q_back; } ;
struct TYPE_4__ {TYPE_1__* q_back; } ;
struct TYPE_3__ {TYPE_2__* q_forw; } ;

/* Variables and functions */

void
remque (struct qelem *elem)
{
  elem -> q_forw -> q_back = elem -> q_back;
  elem -> q_back -> q_forw = elem -> q_forw;
}