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
struct TYPE_2__ {unsigned int hll_line; } ;

/* Variables and functions */
 scalar_t__ listing ; 
 TYPE_1__* listing_tail ; 
 int /*<<< orphan*/  new_frag () ; 

void
listing_source_line (unsigned int line)
{
  if (listing)
    {
      new_frag ();
      listing_tail->hll_line = line;
      new_frag ();
    }
}