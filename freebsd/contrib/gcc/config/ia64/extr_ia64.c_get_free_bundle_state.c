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
struct bundle_state {scalar_t__ unique_num; struct bundle_state* allocated_states_chain; void* dfa_state; struct bundle_state* next; } ;

/* Variables and functions */
 struct bundle_state* allocated_bundle_states_chain ; 
 int /*<<< orphan*/  bundle_states_num ; 
 int dfa_state_size ; 
 struct bundle_state* free_bundle_state_chain ; 
 void* xmalloc (int) ; 

__attribute__((used)) static struct bundle_state *
get_free_bundle_state (void)
{
  struct bundle_state *result;

  if (free_bundle_state_chain != NULL)
    {
      result = free_bundle_state_chain;
      free_bundle_state_chain = result->next;
    }
  else
    {
      result = xmalloc (sizeof (struct bundle_state));
      result->dfa_state = xmalloc (dfa_state_size);
      result->allocated_states_chain = allocated_bundle_states_chain;
      allocated_bundle_states_chain = result;
    }
  result->unique_num = bundle_states_num++;
  return result;

}