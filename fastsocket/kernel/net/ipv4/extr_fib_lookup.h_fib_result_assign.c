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
struct fib_result {struct fib_info* fi; } ;
struct fib_info {int /*<<< orphan*/  fib_clntref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib_info_put (struct fib_info*) ; 

__attribute__((used)) static inline void fib_result_assign(struct fib_result *res,
				     struct fib_info *fi)
{
	if (res->fi != NULL)
		fib_info_put(res->fi);
	res->fi = fi;
	if (fi != NULL)
		atomic_inc(&fi->fib_clntref);
}