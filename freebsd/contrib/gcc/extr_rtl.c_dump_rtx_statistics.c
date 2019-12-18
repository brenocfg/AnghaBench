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

/* Variables and functions */
 char* GET_RTX_NAME (int) ; 
 int LAST_AND_UNUSED_RTX_CODE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int rtvec_alloc_counts ; 
 int rtvec_alloc_sizes ; 
 int* rtx_alloc_counts ; 
 int* rtx_alloc_sizes ; 
 int /*<<< orphan*/  stderr ; 

void
dump_rtx_statistics (void)
{
#ifdef GATHER_STATISTICS
  int i;
  int total_counts = 0;
  int total_sizes = 0;
  fprintf (stderr, "\nRTX Kind               Count      Bytes\n");
  fprintf (stderr, "---------------------------------------\n");
  for (i = 0; i < LAST_AND_UNUSED_RTX_CODE; i++)
    if (rtx_alloc_counts[i])
      {
        fprintf (stderr, "%-20s %7d %10d\n", GET_RTX_NAME (i),
                 rtx_alloc_counts[i], rtx_alloc_sizes[i]);
        total_counts += rtx_alloc_counts[i];
        total_sizes += rtx_alloc_sizes[i];
      }
  if (rtvec_alloc_counts)
    {
      fprintf (stderr, "%-20s %7d %10d\n", "rtvec",
               rtvec_alloc_counts, rtvec_alloc_sizes);
      total_counts += rtvec_alloc_counts;
      total_sizes += rtvec_alloc_sizes;
    }
  fprintf (stderr, "---------------------------------------\n");
  fprintf (stderr, "%-20s %7d %10d\n",
           "Total", total_counts, total_sizes);
  fprintf (stderr, "---------------------------------------\n");
#endif  
}