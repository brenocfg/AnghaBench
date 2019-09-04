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
struct md5 {int dummy; } ;

/* Variables and functions */
 int KEY_MAX ; 
 unsigned int SALT_MAX ; 
 int /*<<< orphan*/  md5_init (struct md5*) ; 
 int /*<<< orphan*/  md5_sum (struct md5*,unsigned char*) ; 
 int /*<<< orphan*/  md5_update (struct md5*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned int strnlen (char const*,int) ; 
 char* to64 (char*,unsigned char,int) ; 

__attribute__((used)) static char *md5crypt(const char *key, const char *setting, char *output)
{
	struct md5 ctx;
	unsigned char md[16];
	unsigned int i, klen, slen;
	const char *salt;
	char *p;

	/* reject large keys */
	klen = strnlen(key, KEY_MAX+1);
	if (klen > KEY_MAX)
		return 0;

	/* setting: $1$salt$ (closing $ is optional) */
	if (strncmp(setting, "$1$", 3) != 0)
		return 0;
	salt = setting + 3;
	for (i = 0; i < SALT_MAX && salt[i] && salt[i] != '$'; i++);
	slen = i;

	/* md5(key salt key) */
	md5_init(&ctx);
	md5_update(&ctx, key, klen);
	md5_update(&ctx, salt, slen);
	md5_update(&ctx, key, klen);
	md5_sum(&ctx, md);

	/* md5(key $1$ salt repeated-md weird-key[0]-0) */
	md5_init(&ctx);
	md5_update(&ctx, key, klen);
	md5_update(&ctx, setting, 3 + slen);
	for (i = klen; i > sizeof md; i -= sizeof md)
		md5_update(&ctx, md, sizeof md);
	md5_update(&ctx, md, i);
	md[0] = 0;
	for (i = klen; i; i >>= 1)
		if (i & 1)
			md5_update(&ctx, md, 1);
		else
			md5_update(&ctx, key, 1);
	md5_sum(&ctx, md);

	/* md = f(md, key, salt) iteration */
	for (i = 0; i < 1000; i++) {
		md5_init(&ctx);
		if (i % 2)
			md5_update(&ctx, key, klen);
		else
			md5_update(&ctx, md, sizeof md);
		if (i % 3)
			md5_update(&ctx, salt, slen);
		if (i % 7)
			md5_update(&ctx, key, klen);
		if (i % 2)
			md5_update(&ctx, md, sizeof md);
		else
			md5_update(&ctx, key, klen);
		md5_sum(&ctx, md);
	}

	/* output is $1$salt$hash */
	memcpy(output, setting, 3 + slen);
	p = output + 3 + slen;
	*p++ = '$';
	static const unsigned char perm[][3] = {
		0,6,12,1,7,13,2,8,14,3,9,15,4,10,5 };
	for (i=0; i<5; i++) p = to64(p,
		(md[perm[i][0]]<<16)|(md[perm[i][1]]<<8)|md[perm[i][2]], 4);
	p = to64(p, md[11], 2);
	*p = 0;

	return output;
}