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
typedef  int /*<<< orphan*/  abts_suite ;

/* Variables and functions */
 int /*<<< orphan*/ * ADD_SUITE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abts_run_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_dbm ; 

abts_suite *testdbm(abts_suite *suite)
{
    suite = ADD_SUITE(suite);

#if APU_HAVE_GDBM
    abts_run_test(suite, test_dbm, "gdbm");
#endif
#if APU_HAVE_NDBM
    abts_run_test(suite, test_dbm, "ndbm");
#endif
#if APU_HAVE_SDBM
    abts_run_test(suite, test_dbm, "sdbm");
#endif
#if APU_HAVE_DB
    abts_run_test(suite, test_dbm, "db");
#endif

    return suite;
}