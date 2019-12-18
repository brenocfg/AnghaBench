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
typedef  int /*<<< orphan*/  apr_ldap_err_t ;
typedef  int /*<<< orphan*/  abts_suite ;

/* Variables and functions */
 int /*<<< orphan*/ * ADD_SUITE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abts_run_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_ldap_ssl_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ get_ldap_host () ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  test_ldap ; 
 int /*<<< orphan*/  test_ldap_tls ; 
 int /*<<< orphan*/  test_ldaps ; 

abts_suite *testldap(abts_suite *suite)
{
#if APR_HAS_LDAP
    apr_ldap_err_t *result = NULL;
    suite = ADD_SUITE(suite);

    apr_ldap_ssl_init(p, NULL, 0, &result);

    if (get_ldap_host()) {
        abts_run_test(suite, test_ldap, NULL);
        abts_run_test(suite, test_ldaps, NULL);
        abts_run_test(suite, test_ldap_tls, NULL);
    }
#endif /* APR_HAS_LDAP */

    return suite;
}