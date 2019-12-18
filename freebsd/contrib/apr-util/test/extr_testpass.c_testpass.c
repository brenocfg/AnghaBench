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
 int /*<<< orphan*/  abts_run_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bcryptpass ; 
 int /*<<< orphan*/  test_crypt ; 
 int /*<<< orphan*/  test_glibc_shapass ; 
 int /*<<< orphan*/  test_md5pass ; 
 int /*<<< orphan*/  test_shapass ; 
 int /*<<< orphan*/  test_threadsafe ; 

abts_suite *testpass(abts_suite *suite)
{
    suite = ADD_SUITE(suite);

#if CRYPT_ALGO_SUPPORTED
    abts_run_test(suite, test_crypt, NULL);
#if APR_HAS_THREADS
    abts_run_test(suite, test_threadsafe, NULL);
#endif
#endif /* CRYPT_ALGO_SUPPORTED */
    abts_run_test(suite, test_shapass, NULL);
    abts_run_test(suite, test_md5pass, NULL);
    abts_run_test(suite, test_bcryptpass, NULL);
#ifdef GLIBCSHA_ALGO_SUPPORTED
    abts_run_test(suite, test_glibc_shapass, NULL);
#endif
    
    return suite;
}