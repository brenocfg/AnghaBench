#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ cur; scalar_t__ end; } ;
typedef  TYPE_1__ reshape_iter ;

/* Variables and functions */
 int /*<<< orphan*/  BRACE_ENCLOSED_INITIALIZER_P (scalar_t__) ; 
 int CONSTRUCTOR_ELTS (scalar_t__) ; 
 int VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VEC_empty (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VEC_index (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  constructor_elt ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gc ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ reshape_init_r (scalar_t__,TYPE_1__*,int) ; 
 int v ; 

tree
reshape_init (tree type, tree init)
{
  VEC(constructor_elt, gc) *v;
  reshape_iter d;
  tree new_init;

  gcc_assert (BRACE_ENCLOSED_INITIALIZER_P (init));

  v = CONSTRUCTOR_ELTS (init);

  /* An empty constructor does not need reshaping, and it is always a valid
     initializer.  */
  if (VEC_empty (constructor_elt, v))
    return init;

  /* Recurse on this CONSTRUCTOR.  */
  d.cur = VEC_index (constructor_elt, v, 0);
  d.end = d.cur + VEC_length (constructor_elt, v);

  new_init = reshape_init_r (type, &d, true);
  if (new_init == error_mark_node)
    return error_mark_node;

  /* Make sure all the element of the constructor were used. Otherwise,
     issue an error about exceeding initializers.  */
  if (d.cur != d.end)
    error ("too many initializers for %qT", type);

  return new_init;
}