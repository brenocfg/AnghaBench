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
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */
 scalar_t__ cputime_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_zero ; 

__attribute__((used)) static inline int expires_gt(cputime_t expires, cputime_t new_exp)
{
	return cputime_eq(expires, cputime_zero) ||
	       cputime_gt(expires, new_exp);
}