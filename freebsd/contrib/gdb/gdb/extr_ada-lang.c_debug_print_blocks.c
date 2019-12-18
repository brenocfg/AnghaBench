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
struct blockvector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (struct blockvector*,int) ; 
 int BLOCKVECTOR_NBLOCKS (struct blockvector*) ; 
 int /*<<< orphan*/  debug_print_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
debug_print_blocks (struct blockvector *bv)
{
  int i;

  if (bv == NULL)
    return;
  for (i = 0; i < BLOCKVECTOR_NBLOCKS (bv); i += 1)
    {
      fprintf (stderr, "%6d. ", i);
      debug_print_block (BLOCKVECTOR_BLOCK (bv, i));
    }
}