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
typedef  void* tree ;
struct z_candidate {size_t num_convs; int viable; struct z_candidate* next; void* conversion_path; void* access_path; int /*<<< orphan*/ ** convs; void* args; void* fn; } ;
typedef  int /*<<< orphan*/  conversion ;

/* Variables and functions */
 scalar_t__ conversion_obstack_alloc (int) ; 

__attribute__((used)) static struct z_candidate *
add_candidate (struct z_candidate **candidates,
	       tree fn, tree args,
	       size_t num_convs, conversion **convs,
	       tree access_path, tree conversion_path,
	       int viable)
{
  struct z_candidate *cand = (struct z_candidate *)
    conversion_obstack_alloc (sizeof (struct z_candidate));

  cand->fn = fn;
  cand->args = args;
  cand->convs = convs;
  cand->num_convs = num_convs;
  cand->access_path = access_path;
  cand->conversion_path = conversion_path;
  cand->viable = viable;
  cand->next = *candidates;
  *candidates = cand;

  return cand;
}