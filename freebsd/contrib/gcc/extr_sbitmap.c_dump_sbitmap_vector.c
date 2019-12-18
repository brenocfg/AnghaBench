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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_sbitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
dump_sbitmap_vector (FILE *file, const char *title, const char *subtitle,
		     sbitmap *bmaps, int n_maps)
{
  int bb;

  fprintf (file, "%s\n", title);
  for (bb = 0; bb < n_maps; bb++)
    {
      fprintf (file, "%s %d\n", subtitle, bb);
      dump_sbitmap (file, bmaps[bb]);
    }

  fprintf (file, "\n");
}