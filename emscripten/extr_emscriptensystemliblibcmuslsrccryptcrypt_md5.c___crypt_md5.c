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
 char* md5crypt (char const*,char const*,char*) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 

char *__crypt_md5(const char *key, const char *setting, char *output)
{
	static const char testkey[] = "Xy01@#\x01\x02\x80\x7f\xff\r\n\x81\t !";
	static const char testsetting[] = "$1$abcd0123$";
	static const char testhash[] = "$1$abcd0123$9Qcg8DyviekV3tDGMZynJ1";
	char testbuf[64];
	char *p, *q;

	p = md5crypt(key, setting, output);
	/* self test and stack cleanup */
	q = md5crypt(testkey, testsetting, testbuf);
	if (!p || q != testbuf || memcmp(testbuf, testhash, sizeof testhash))
		return "*";
	return p;
}