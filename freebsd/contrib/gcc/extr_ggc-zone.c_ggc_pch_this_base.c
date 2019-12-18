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
struct TYPE_2__ {scalar_t__* type_totals; } ;
struct ggc_pch_data {size_t base; size_t orig_base; size_t* type_bases; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/ * alloc_bits; TYPE_1__ d; } ;

/* Variables and functions */
 int NUM_PCH_BUCKETS ; 
 int /*<<< orphan*/ * xcalloc (int,int /*<<< orphan*/ ) ; 

void
ggc_pch_this_base (struct ggc_pch_data *d, void *base_)
{
  int i;
  size_t base = (size_t) base_;

  d->base = d->orig_base = base;
  for (i = 0; i < NUM_PCH_BUCKETS; i++)
    {
      d->type_bases[i] = base;
      base += d->d.type_totals[i];
    }

  if (d->alloc_bits == NULL)
    d->alloc_bits = xcalloc (1, d->alloc_size);
}