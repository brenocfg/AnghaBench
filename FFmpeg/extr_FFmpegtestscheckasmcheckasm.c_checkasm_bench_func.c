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
struct TYPE_4__ {int /*<<< orphan*/  bench_pattern_len; scalar_t__ bench_pattern; TYPE_1__* current_func; int /*<<< orphan*/  num_failed; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__ state ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int checkasm_bench_func(void)
{
    return !state.num_failed && state.bench_pattern &&
           !strncmp(state.current_func->name, state.bench_pattern, state.bench_pattern_len);
}