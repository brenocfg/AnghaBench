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
struct mem_ref {int /*<<< orphan*/  vops; int /*<<< orphan*/  locs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mem_ref*) ; 
 int /*<<< orphan*/  free_mem_ref_locs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_mem_ref (struct mem_ref *ref)
{
  free_mem_ref_locs (ref->locs);
  BITMAP_FREE (ref->vops);
  free (ref);
}