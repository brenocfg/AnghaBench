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
#define  br_md5sha1_ID 133 
#define  br_sha1_ID 132 
#define  br_sha224_ID 131 
#define  br_sha256_ID 130 
#define  br_sha384_ID 129 
#define  br_sha512_ID 128 

__attribute__((used)) static int
choose_hash(unsigned hh)
{
	static const int f[] = {
		br_sha256_ID, br_sha224_ID, br_sha384_ID, br_sha512_ID,
		br_sha1_ID, br_md5sha1_ID, -1
	};

	size_t u;

	for (u = 0; f[u] >= 0; u ++) {
		if (((hh >> f[u]) & 1) != 0) {
			return f[u];
		}
	}
	return -1;
}