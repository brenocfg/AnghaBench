#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ opt; } ;
typedef  TYPE_1__ opt_apply ;

/* Variables and functions */
 void stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void
apply_opts(void (*op) (opt_apply *, int), opt_apply ppp[], int b)
{
  opt_apply *pp;

  for (pp = ppp; pp->opt; pp++)
    (*op) (pp, b);
}