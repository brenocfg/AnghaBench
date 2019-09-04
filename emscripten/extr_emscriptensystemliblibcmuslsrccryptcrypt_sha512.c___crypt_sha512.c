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
 char* sha512crypt (char const*,char const*,char*) ; 

char *__crypt_sha512(const char *key, const char *setting, char *output)
{
	static const char testkey[] = "Xy01@#\x01\x02\x80\x7f\xff\r\n\x81\t !";
	static const char testsetting[] = "$6$rounds=1234$abc0123456789$";
	static const char testhash[] = "$6$rounds=1234$abc0123456789$BCpt8zLrc/RcyuXmCDOE1ALqMXB2MH6n1g891HhFj8.w7LxGv.FTkqq6Vxc/km3Y0jE0j24jY5PIv/oOu6reg1";
	char testbuf[128];
	char *p, *q;

	p = sha512crypt(key, setting, output);
	/* self test and stack cleanup */
	q = sha512crypt(testkey, testsetting, testbuf);
	if (!p || q != testbuf || memcmp(testbuf, testhash, sizeof testhash))
		return "*";
	return p;
}