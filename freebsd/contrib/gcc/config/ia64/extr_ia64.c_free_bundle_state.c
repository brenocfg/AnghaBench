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
struct bundle_state {struct bundle_state* next; } ;

/* Variables and functions */
 struct bundle_state* free_bundle_state_chain ; 

__attribute__((used)) static void
free_bundle_state (struct bundle_state *state)
{
  state->next = free_bundle_state_chain;
  free_bundle_state_chain = state;
}