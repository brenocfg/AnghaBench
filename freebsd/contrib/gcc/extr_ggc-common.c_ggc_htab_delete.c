#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ggc_cache_tab {int /*<<< orphan*/  (* cb ) (void*) ;int /*<<< orphan*/ * base; int /*<<< orphan*/  (* marked_p ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  htab_clear_slot (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static int
ggc_htab_delete (void **slot, void *info)
{
  const struct ggc_cache_tab *r = (const struct ggc_cache_tab *) info;

  if (! (*r->marked_p) (*slot))
    htab_clear_slot (*r->base, slot);
  else
    (*r->cb) (*slot);

  return 1;
}