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
struct TYPE_3__ {int* totals; } ;
struct ggc_pch_data {size_t* base; TYPE_1__ d; } ;
struct TYPE_4__ {int /*<<< orphan*/  pagesize; } ;

/* Variables and functions */
 TYPE_2__ G ; 
 unsigned int NUM_ORDERS ; 
 int OBJECT_SIZE (unsigned int) ; 
 scalar_t__ ROUND_UP (int,int /*<<< orphan*/ ) ; 

void
ggc_pch_this_base (struct ggc_pch_data *d, void *base)
{
  size_t a = (size_t) base;
  unsigned i;

  for (i = 0; i < NUM_ORDERS; i++)
    {
      d->base[i] = a;
      a += ROUND_UP (d->d.totals[i] * OBJECT_SIZE (i), G.pagesize);
    }
}