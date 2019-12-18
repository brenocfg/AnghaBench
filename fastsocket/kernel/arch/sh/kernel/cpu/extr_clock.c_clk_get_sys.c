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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clk* clk_find (char const*,char const*) ; 
 int /*<<< orphan*/  clock_list_sem ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct clk *clk_get_sys(const char *dev_id, const char *con_id)
{
	struct clk *clk;

	mutex_lock(&clock_list_sem);
	clk = clk_find(dev_id, con_id);
	mutex_unlock(&clock_list_sem);

	return clk ? clk : ERR_PTR(-ENOENT);
}