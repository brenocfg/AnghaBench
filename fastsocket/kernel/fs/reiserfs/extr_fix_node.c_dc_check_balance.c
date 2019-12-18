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
struct tree_balance {int /*<<< orphan*/  tb_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int dc_check_balance_internal (struct tree_balance*,int) ; 
 int dc_check_balance_leaf (struct tree_balance*,int) ; 

__attribute__((used)) static int dc_check_balance(struct tree_balance *tb, int h)
{
	RFALSE(!(PATH_H_PBUFFER(tb->tb_path, h)),
	       "vs-8250: S is not initialized");

	if (h)
		return dc_check_balance_internal(tb, h);
	else
		return dc_check_balance_leaf(tb, h);
}