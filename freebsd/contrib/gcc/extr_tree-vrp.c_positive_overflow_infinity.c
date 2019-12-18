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
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_overflow_infinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supports_overflow_infinity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
positive_overflow_infinity (tree type)
{
#ifdef ENABLE_CHECKING
  gcc_assert (supports_overflow_infinity (type));
#endif
  return make_overflow_infinity (TYPE_MAX_VALUE (type));
}