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
struct gcov_iterator {int /*<<< orphan*/  function; int /*<<< orphan*/  info; } ;
struct gcov_fn_info {int dummy; } ;

/* Variables and functions */
 struct gcov_fn_info* get_fn_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gcov_fn_info *get_func(struct gcov_iterator *iter)
{
	return get_fn_info(iter->info, iter->function);
}