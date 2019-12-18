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
struct def_blocks_d {int /*<<< orphan*/  livein_blocks; int /*<<< orphan*/  phi_blocks; int /*<<< orphan*/  def_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct def_blocks_d*) ; 

__attribute__((used)) static void
def_blocks_free (void *p)
{
  struct def_blocks_d *entry = (struct def_blocks_d *) p;
  BITMAP_FREE (entry->def_blocks);
  BITMAP_FREE (entry->phi_blocks);
  BITMAP_FREE (entry->livein_blocks);
  free (entry);
}