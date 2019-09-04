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
 char* __crypt_r (char const*,char const*,struct crypt_data*) ; 

char *crypt(const char *key, const char *salt)
{
	/* This buffer is sufficiently large for all
	 * currently-supported hash types. It needs to be updated if
	 * longer hashes are added. The cast to struct crypt_data * is
	 * purely to meet the public API requirements of the crypt_r
	 * function; the implementation of crypt_r uses the object
	 * purely as a char buffer. */
	static char buf[128];
	return __crypt_r(key, salt, (struct crypt_data *)buf);
}