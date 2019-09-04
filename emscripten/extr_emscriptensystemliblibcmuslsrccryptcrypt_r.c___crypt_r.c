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
struct crypt_data {int dummy; } ;

/* Variables and functions */
 char* __crypt_blowfish (char const*,char const*,char*) ; 
 char* __crypt_des (char const*,char const*,char*) ; 
 char* __crypt_md5 (char const*,char const*,char*) ; 
 char* __crypt_sha256 (char const*,char const*,char*) ; 
 char* __crypt_sha512 (char const*,char const*,char*) ; 

char *__crypt_r(const char *key, const char *salt, struct crypt_data *data)
{
	/* Per the crypt_r API, the caller has provided a pointer to
	 * struct crypt_data; however, this implementation does not
	 * use the structure to store any internal state, and treats
	 * it purely as a char buffer for storing the result. */
	char *output = (char *)data;
	if (salt[0] == '$' && salt[1] && salt[2]) {
		if (salt[1] == '1' && salt[2] == '$')
			return __crypt_md5(key, salt, output);
		if (salt[1] == '2' && salt[3] == '$')
			return __crypt_blowfish(key, salt, output);
		if (salt[1] == '5' && salt[2] == '$')
			return __crypt_sha256(key, salt, output);
		if (salt[1] == '6' && salt[2] == '$')
			return __crypt_sha512(key, salt, output);
	}
	return __crypt_des(key, salt, output);
}