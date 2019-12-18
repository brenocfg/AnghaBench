#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ternary_tree ;
struct TYPE_4__ {struct TYPE_4__* hikid; struct TYPE_4__* eqkid; scalar_t__ splitchar; struct TYPE_4__* lokid; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
ternary_cleanup (ternary_tree p)
{
  if (p)
    {
      ternary_cleanup (p->lokid);
      if (p->splitchar)
	ternary_cleanup (p->eqkid);
      ternary_cleanup (p->hikid);
      free (p);
    }
}