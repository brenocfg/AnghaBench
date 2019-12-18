#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int persistent_count; scalar_t__ mudflap_mode; scalar_t__ print_leaks; scalar_t__ collect_stats; } ;

/* Variables and functions */
 unsigned int LOOKUP_CACHE_SIZE ; 
 int /*<<< orphan*/  MAXPTR ; 
 int /*<<< orphan*/  MINPTR ; 
 unsigned int __MF_TYPE_MAX_CEM ; 
 int /*<<< orphan*/  __mf_count_check ; 
 int /*<<< orphan*/  __mf_count_register ; 
 int /*<<< orphan*/  __mf_count_unregister ; 
 int /*<<< orphan*/ * __mf_count_violation ; 
 int /*<<< orphan*/  __mf_describe_object (int /*<<< orphan*/ *) ; 
 unsigned int __mf_find_objects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int __mf_lock_contention ; 
 int* __mf_lookup_cache_reusecount ; 
 scalar_t__** __mf_object_cemetary ; 
 TYPE_1__ __mf_opts ; 
 unsigned int __mf_reentrancy ; 
 unsigned int __mf_report_leaks () ; 
 int /*<<< orphan*/ * __mf_total_register_size ; 
 int /*<<< orphan*/  __mf_total_unregister_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ mode_check ; 
 int /*<<< orphan*/  stderr ; 

void
__mfu_report ()
{
  if (__mf_opts.collect_stats)
    {
      fprintf (stderr,
               "*******\n"
               "mudflap stats:\n"
               "calls to __mf_check: %lu\n"
               "         __mf_register: %lu [%luB, %luB, %luB, %luB, %luB]\n"
               "         __mf_unregister: %lu [%luB]\n"
               "         __mf_violation: [%lu, %lu, %lu, %lu, %lu]\n",
               __mf_count_check,
               __mf_count_register,
               __mf_total_register_size[0], __mf_total_register_size[1],
               __mf_total_register_size[2], __mf_total_register_size[3],
               __mf_total_register_size[4], /* XXX */
               __mf_count_unregister, __mf_total_unregister_size,
               __mf_count_violation[0], __mf_count_violation[1],
               __mf_count_violation[2], __mf_count_violation[3],
               __mf_count_violation[4]);

      fprintf (stderr,
               "calls with reentrancy: %lu\n", __mf_reentrancy);
#ifdef LIBMUDFLAPTH
      fprintf (stderr,
               "           lock contention: %lu\n", __mf_lock_contention);
#endif

      /* Lookup cache stats.  */
      {
        unsigned i;
        unsigned max_reuse = 0;
        unsigned num_used = 0;
        unsigned num_unused = 0;

        for (i = 0; i < LOOKUP_CACHE_SIZE; i++)
          {
            if (__mf_lookup_cache_reusecount[i])
              num_used ++;
            else
              num_unused ++;
            if (max_reuse < __mf_lookup_cache_reusecount[i])
              max_reuse = __mf_lookup_cache_reusecount[i];
          }
        fprintf (stderr, "lookup cache slots used: %u  unused: %u  peak-reuse: %u\n",
                 num_used, num_unused, max_reuse);
      }

      {
        unsigned live_count;
        live_count = __mf_find_objects (MINPTR, MAXPTR, NULL, 0);
        fprintf (stderr, "number of live objects: %u\n", live_count);
      }

      if (__mf_opts.persistent_count > 0)
        {
          unsigned dead_count = 0;
          unsigned row, plot;
          for (row = 0; row <= __MF_TYPE_MAX_CEM; row ++)
            for (plot = 0 ; plot < __mf_opts.persistent_count; plot ++)
              if (__mf_object_cemetary [row][plot] != 0)
                dead_count ++;
          fprintf (stderr, "          zombie objects: %u\n", dead_count);
        }
    }
  if (__mf_opts.print_leaks && (__mf_opts.mudflap_mode == mode_check))
    {
      unsigned l;
      extern void * __mf_wrap_alloca_indirect (size_t c);

      /* Free up any remaining alloca()'d blocks.  */
      __mf_wrap_alloca_indirect (0);
      __mf_describe_object (NULL); /* Reset description epoch.  */
      l = __mf_report_leaks ();
      fprintf (stderr, "number of leaked objects: %u\n", l);
    }
}