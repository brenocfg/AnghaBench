#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unw_word ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
struct unw_state_record {struct unw_labeled_state* labeled_states; TYPE_2__ curr; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct unw_labeled_state {struct unw_labeled_state* next; TYPE_1__ saved_state; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 struct unw_labeled_state* alloc_label_state () ; 
 int /*<<< orphan*/  dup_state_stack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static inline void
desc_label_state (unw_word label, struct unw_state_record *sr)
{
  struct unw_labeled_state *ls = alloc_label_state ();

  ls->label = label;
  memcpy (&ls->saved_state, &sr->curr, sizeof (ls->saved_state));
  ls->saved_state.next = dup_state_stack (sr->curr.next);

  /* Insert into list of labeled states.  */
  ls->next = sr->labeled_states;
  sr->labeled_states = ls;
}