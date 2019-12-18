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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ CONSTANT_CLASS_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  needs_overflow_infinity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
supports_overflow_infinity (tree type)
{
#ifdef ENABLE_CHECKING
  gcc_assert (needs_overflow_infinity (type));
#endif
  return (TYPE_MIN_VALUE (type) != NULL_TREE
	  && CONSTANT_CLASS_P (TYPE_MIN_VALUE (type))
	  && TYPE_MAX_VALUE (type) != NULL_TREE
	  && CONSTANT_CLASS_P (TYPE_MAX_VALUE (type)));
}