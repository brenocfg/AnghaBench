#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sbitmap ;
struct TYPE_3__ {unsigned int size; unsigned int n_bits; unsigned int* elms; } ;
typedef  unsigned int SBITMAP_ELT_TYPE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int SBITMAP_ELT_BITS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
dump_sbitmap (FILE *file, sbitmap bmap)
{
  unsigned int i, n, j;
  unsigned int set_size = bmap->size;
  unsigned int total_bits = bmap->n_bits;

  fprintf (file, "  ");
  for (i = n = 0; i < set_size && n < total_bits; i++)
    for (j = 0; j < SBITMAP_ELT_BITS && n < total_bits; j++, n++)
      {
	if (n != 0 && n % 10 == 0)
	  fprintf (file, " ");

	fprintf (file, "%d",
		 (bmap->elms[i] & ((SBITMAP_ELT_TYPE) 1 << j)) != 0);
      }

  fprintf (file, "\n");
}