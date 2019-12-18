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
typedef  int /*<<< orphan*/  jacobian ;
typedef  int /*<<< orphan*/  curve_params ;

/* Variables and functions */
 int /*<<< orphan*/  code_double ; 
 int /*<<< orphan*/  run_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
point_double(jacobian *P, const curve_params *cc)
{
	run_code(P, P, cc, code_double);
}