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
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ASSERT_FAILURE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_assert_success (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_password_validate (char const*,char*) ; 
 int /*<<< orphan*/  apr_sha1_base64 (char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void test_shapass(abts_case *tc, void *data)
{
    const char *pass = "hellojed";
    const char *pass2 = "hellojed2";
    char hash[100];

    apr_sha1_base64(pass, strlen(pass), hash);

    apr_assert_success(tc, "SHA1 password validated",
                       apr_password_validate(pass, hash));
    APR_ASSERT_FAILURE(tc, "wrong SHA1 password should not validate",
                       apr_password_validate(pass2, hash));
}