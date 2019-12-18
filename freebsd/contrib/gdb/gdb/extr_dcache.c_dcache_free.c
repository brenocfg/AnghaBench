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
struct TYPE_5__ {struct TYPE_5__* the_cache; } ;
typedef  TYPE_1__ DCACHE ;

/* Variables and functions */
 TYPE_1__* last_cache ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
dcache_free (DCACHE *dcache)
{
  if (last_cache == dcache)
    last_cache = NULL;

  xfree (dcache->the_cache);
  xfree (dcache);
}