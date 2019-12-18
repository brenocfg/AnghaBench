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
struct TYPE_2__ {int what; } ;

/* Variables and functions */
 int n_replacements ; 
 TYPE_1__* replacements ; 

void
transfer_replacements (int to, int from)
{
  int i;

  for (i = 0; i < n_replacements; i++)
    if (replacements[i].what == from)
      replacements[i].what = to;
}