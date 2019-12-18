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
 int br_md5_ID ; 
 int br_sha1_ID ; 
 int br_sha224_ID ; 
 int br_sha256_ID ; 
 int br_sha384_ID ; 
 int br_sha512_ID ; 
 scalar_t__ eqstring (char*,char*) ; 

__attribute__((used)) static int
string_to_hash(const char *name)
{
	char tmp[20];
	size_t u, v;

	for (u = 0, v = 0; name[u]; u ++) {
		int c;

		c = name[u];
		if ((c >= '0' && c <= '9')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'))
		{
			tmp[v ++] = c;
			if (v == sizeof tmp) {
				return -1;
			}
		}
	}
	tmp[v] = 0;
	if (eqstring(tmp, "md5")) {
		return br_md5_ID;
	} else if (eqstring(tmp, "sha1")) {
		return br_sha1_ID;
	} else if (eqstring(tmp, "sha224")) {
		return br_sha224_ID;
	} else if (eqstring(tmp, "sha256")) {
		return br_sha256_ID;
	} else if (eqstring(tmp, "sha384")) {
		return br_sha384_ID;
	} else if (eqstring(tmp, "sha512")) {
		return br_sha512_ID;
	} else {
		return -1;
	}
}