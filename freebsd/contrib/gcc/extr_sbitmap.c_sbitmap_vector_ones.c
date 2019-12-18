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
typedef  int /*<<< orphan*/  sbitmap ;

/* Variables and functions */
 int /*<<< orphan*/  sbitmap_ones (int /*<<< orphan*/ ) ; 

void
sbitmap_vector_ones (sbitmap *bmap, unsigned int n_vecs)
{
  unsigned int i;

  for (i = 0; i < n_vecs; i++)
    sbitmap_ones (bmap[i]);
}