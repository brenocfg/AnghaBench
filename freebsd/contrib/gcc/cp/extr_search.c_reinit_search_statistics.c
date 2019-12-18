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
 scalar_t__ n_calls_get_base_type ; 
 scalar_t__ n_calls_lookup_field ; 
 scalar_t__ n_calls_lookup_field_1 ; 
 scalar_t__ n_calls_lookup_fnfields ; 
 scalar_t__ n_calls_lookup_fnfields_1 ; 
 scalar_t__ n_contexts_saved ; 
 scalar_t__ n_fields_searched ; 
 scalar_t__ n_outer_fields_searched ; 

void
reinit_search_statistics (void)
{
#ifdef GATHER_STATISTICS
  n_fields_searched = 0;
  n_calls_lookup_field = 0, n_calls_lookup_field_1 = 0;
  n_calls_lookup_fnfields = 0, n_calls_lookup_fnfields_1 = 0;
  n_calls_get_base_type = 0;
  n_outer_fields_searched = 0;
  n_contexts_saved = 0;
#endif /* GATHER_STATISTICS */
}