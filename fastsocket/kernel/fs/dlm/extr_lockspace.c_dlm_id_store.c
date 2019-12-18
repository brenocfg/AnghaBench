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
struct dlm_ls {int /*<<< orphan*/  ls_global_id; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dlm_id_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	ls->ls_global_id = simple_strtoul(buf, NULL, 0);
	return len;
}