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
struct gcov_summary {struct gcov_ctr_summary* ctrs; void* checksum; } ;
struct gcov_ctr_summary {void* sum_max; void* run_max; void* sum_all; void* runs; void* num; } ;

/* Variables and functions */
 unsigned int GCOV_COUNTERS_SUMMABLE ; 
 void* gcov_read_counter () ; 
 void* gcov_read_unsigned () ; 

void
gcov_read_summary (struct gcov_summary *summary)
{
  unsigned ix;
  struct gcov_ctr_summary *csum;
  
  summary->checksum = gcov_read_unsigned ();
  for (csum = summary->ctrs, ix = GCOV_COUNTERS_SUMMABLE; ix--; csum++)
    {
      csum->num = gcov_read_unsigned ();
      csum->runs = gcov_read_unsigned ();
      csum->sum_all = gcov_read_counter ();
      csum->run_max = gcov_read_counter ();
      csum->sum_max = gcov_read_counter ();
    }
}