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
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_WRAPS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
needs_overflow_infinity (tree type)
{
  return INTEGRAL_TYPE_P (type) && !TYPE_OVERFLOW_WRAPS (type);
}