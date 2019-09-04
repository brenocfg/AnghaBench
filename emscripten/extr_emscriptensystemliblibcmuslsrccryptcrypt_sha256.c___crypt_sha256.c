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
 scalar_t__ memcmp (char*,char const*,int) ; 
 char* sha256crypt (char const*,char const*,char*) ; 

char *__crypt_sha256(const char *key, const char *setting, char *output)
{
	static const char testkey[] = "Xy01@#\x01\x02\x80\x7f\xff\r\n\x81\t !";
	static const char testsetting[] = "$5$rounds=1234$abc0123456789$";
	static const char testhash[] = "$5$rounds=1234$abc0123456789$3VfDjPt05VHFn47C/ojFZ6KRPYrOjj1lLbH.dkF3bZ6";
	char testbuf[128];
	char *p, *q;

	p = sha256crypt(key, setting, output);
	/* self test and stack cleanup */
	q = sha256crypt(testkey, testsetting, testbuf);
	if (!p || q != testbuf || memcmp(testbuf, testhash, sizeof testhash))
		return "*";
	return p;
}