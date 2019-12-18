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
struct TYPE_3__ {int /*<<< orphan*/  stmt; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 scalar_t__ OMP_PARALLEL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_parallel_ctx (omp_context *ctx)
{
  return TREE_CODE (ctx->stmt) == OMP_PARALLEL;
}