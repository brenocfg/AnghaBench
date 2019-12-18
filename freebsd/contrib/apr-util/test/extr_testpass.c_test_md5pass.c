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
 int /*<<< orphan*/  apr_md5_encode (char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  apr_password_validate (char const*,char*) ; 

__attribute__((used)) static void test_md5pass(abts_case *tc, void *data)
{
    const char *pass = "hellojed", *salt = "sardine";
    const char *pass2 = "hellojed2";
    char hash[100];

    apr_md5_encode(pass, salt, hash, sizeof hash);

    apr_assert_success(tc, "MD5 password validated",
                       apr_password_validate(pass, hash));
    APR_ASSERT_FAILURE(tc, "wrong MD5 password should not validate",
                       apr_password_validate(pass2, hash));
}