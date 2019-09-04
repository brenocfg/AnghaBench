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

/* Variables and functions */
 char const _PASSWORD_EFMT1 ; 
 void* _crypt_extended_r_uut (char const*,char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

char *__crypt_des(const char *key, const char *setting, char *output)
{
	const char *test_key = "\x80\xff\x80\x01 "
	    "\x7f\x81\x80\x80\x0d\x0a\xff\x7f \x81 test";
	const char *test_setting = "_0.../9Zz";
	const char *test_hash = "_0.../9ZzX7iSJNd21sU";
	char test_buf[21];
	char *retval;
	const char *p;

	if (*setting != _PASSWORD_EFMT1) {
		test_setting = "\x80x";
		test_hash = "\x80x22/wK52ZKGA";
	}

	/*
	 * Hash the supplied password.
	 */
	retval = _crypt_extended_r_uut(key, setting, output);

	/*
	 * Perform a quick self-test.  It is important that we make both calls
	 * to _crypt_extended_r_uut() from the same scope such that they likely
	 * use the same stack locations, which makes the second call overwrite
	 * the first call's sensitive data on the stack and makes it more
	 * likely that any alignment related issues would be detected.
	 */
	p = _crypt_extended_r_uut(test_key, test_setting, test_buf);
	if (p && !strcmp(p, test_hash) && retval)
		return retval;

	return (setting[0]=='*') ? "x" : "*";
}