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
struct fib_result {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FIB_RES_DEV (struct fib_result) ; 
 int /*<<< orphan*/  FIB_RES_GW (struct fib_result) ; 
 int /*<<< orphan*/  inet_select_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__be32 __fib_res_prefsrc(struct fib_result *res)
{
	return inet_select_addr(FIB_RES_DEV(*res), FIB_RES_GW(*res), res->scope);
}