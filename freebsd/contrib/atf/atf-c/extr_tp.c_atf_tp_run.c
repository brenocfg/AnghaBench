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
typedef  int /*<<< orphan*/  atf_tp_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_run (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * find_tc (int /*<<< orphan*/  const*,char const*) ; 

atf_error_t
atf_tp_run(const atf_tp_t *tp, const char *tcname, const char *resfile)
{
    const atf_tc_t *tc;

    tc = find_tc(tp, tcname);
    PRE(tc != NULL);

    return atf_tc_run(tc, resfile);
}