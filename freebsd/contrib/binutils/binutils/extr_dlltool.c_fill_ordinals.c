#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ordinal; } ;
typedef  TYPE_1__ export_type ;

/* Variables and functions */
 int d_high_ord ; 
 int d_low_ord ; 
 int d_nfuncs ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfunc ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
fill_ordinals (export_type **d_export_vec)
{
  int lowest = -1;
  int i;
  char *ptr;
  int size = 65536;

  qsort (d_export_vec, d_nfuncs, sizeof (export_type *), pfunc);

  /* Fill in the unset ordinals with ones from our range.  */
  ptr = (char *) xmalloc (size);

  memset (ptr, 0, size);

  /* Mark in our large vector all the numbers that are taken.  */
  for (i = 0; i < d_nfuncs; i++)
    {
      if (d_export_vec[i]->ordinal != -1)
	{
	  ptr[d_export_vec[i]->ordinal] = 1;

	  if (lowest == -1 || d_export_vec[i]->ordinal < lowest)
	    lowest = d_export_vec[i]->ordinal;
	}
    }

  /* Start at 1 for compatibility with MS toolchain.  */
  if (lowest == -1)
    lowest = 1;

  /* Now fill in ordinals where the user wants us to choose.  */
  for (i = 0; i < d_nfuncs; i++)
    {
      if (d_export_vec[i]->ordinal == -1)
	{
	  int j;

	  /* First try within or after any user supplied range.  */
	  for (j = lowest; j < size; j++)
	    if (ptr[j] == 0)
	      {
		ptr[j] = 1;
		d_export_vec[i]->ordinal = j;
		goto done;
	      }

	  /* Then try before the range.  */
	  for (j = lowest; j >0; j--)
	    if (ptr[j] == 0)
	      {
		ptr[j] = 1;
		d_export_vec[i]->ordinal = j;
		goto done;
	      }
	done:;
	}
    }

  free (ptr);

  /* And resort.  */
  qsort (d_export_vec, d_nfuncs, sizeof (export_type *), pfunc);

  /* Work out the lowest and highest ordinal numbers.  */
  if (d_nfuncs)
    {
      if (d_export_vec[0])
	d_low_ord = d_export_vec[0]->ordinal;
      if (d_export_vec[d_nfuncs-1])
	d_high_ord = d_export_vec[d_nfuncs-1]->ordinal;
    }
}