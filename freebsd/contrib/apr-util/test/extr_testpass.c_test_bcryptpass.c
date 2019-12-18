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
typedef  int /*<<< orphan*/  salt ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ASSERT_FAILURE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_assert_success (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_bcrypt_encode (char const*,int,unsigned char*,int,char*,int) ; 
 int /*<<< orphan*/  apr_password_validate (char const*,char const*) ; 

__attribute__((used)) static void test_bcryptpass(abts_case *tc, void *data)
{
    const char *pass = "hellojed";
    const char *pass2 = "hellojed2";
    unsigned char salt[] = "sardine_sardine";
    char hash[100];
    const char *hash2 = "$2a$08$qipUJiI9fySUN38hcbz.lucXvAmtgowKOWYtB9y3CXyl6lTknruou";
    const char *pass3 = "foobar";

    apr_assert_success(tc, "bcrypt encode password", 
                       apr_bcrypt_encode(pass, 5, salt, sizeof(salt), hash,
                                         sizeof(hash)));

    apr_assert_success(tc, "bcrypt password validated",
                       apr_password_validate(pass, hash));
    APR_ASSERT_FAILURE(tc, "wrong bcrypt password should not validate",
                       apr_password_validate(pass2, hash));
    apr_assert_success(tc, "bcrypt password validated",
                       apr_password_validate(pass3, hash2));
}