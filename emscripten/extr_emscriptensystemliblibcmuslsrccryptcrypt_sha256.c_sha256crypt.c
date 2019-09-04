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
struct sha256 {int dummy; } ;

/* Variables and functions */
 int KEY_MAX ; 
 unsigned int ROUNDS_DEFAULT ; 
 unsigned long ROUNDS_MAX ; 
 unsigned long ROUNDS_MIN ; 
 unsigned int SALT_MAX ; 
 int /*<<< orphan*/  hashmd (struct sha256*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  sha256_init (struct sha256*) ; 
 int /*<<< orphan*/  sha256_sum (struct sha256*,unsigned char*) ; 
 int /*<<< orphan*/  sha256_update (struct sha256*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned int strnlen (char const*,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 char* to64 (char*,unsigned char,int) ; 

__attribute__((used)) static char *sha256crypt(const char *key, const char *setting, char *output)
{
	struct sha256 ctx;
	unsigned char md[32], kmd[32], smd[32];
	unsigned int i, r, klen, slen;
	char rounds[20] = "";
	const char *salt;
	char *p;

	/* reject large keys */
	klen = strnlen(key, KEY_MAX+1);
	if (klen > KEY_MAX)
		return 0;

	/* setting: $5$rounds=n$salt$ (rounds=n$ and closing $ are optional) */
	if (strncmp(setting, "$5$", 3) != 0)
		return 0;
	salt = setting + 3;

	r = ROUNDS_DEFAULT;
	if (strncmp(salt, "rounds=", sizeof "rounds=" - 1) == 0) {
		unsigned long u;
		char *end;

		/*
		 * this is a deviation from the reference:
		 * bad rounds setting is rejected if it is
		 * - empty
		 * - unterminated (missing '$')
		 * - begins with anything but a decimal digit
		 * the reference implementation treats these bad
		 * rounds as part of the salt or parse them with
		 * strtoul semantics which may cause problems
		 * including non-portable hashes that depend on
		 * the host's value of ULONG_MAX.
		 */
		salt += sizeof "rounds=" - 1;
		if (!isdigit(*salt))
			return 0;
		u = strtoul(salt, &end, 10);
		if (*end != '$')
			return 0;
		salt = end+1;
		if (u < ROUNDS_MIN)
			r = ROUNDS_MIN;
		else if (u > ROUNDS_MAX)
			return 0;
		else
			r = u;
		/* needed when rounds is zero prefixed or out of bounds */
		sprintf(rounds, "rounds=%u$", r);
	}

	for (i = 0; i < SALT_MAX && salt[i] && salt[i] != '$'; i++)
		/* reject characters that interfere with /etc/shadow parsing */
		if (salt[i] == '\n' || salt[i] == ':')
			return 0;
	slen = i;

	/* B = sha(key salt key) */
	sha256_init(&ctx);
	sha256_update(&ctx, key, klen);
	sha256_update(&ctx, salt, slen);
	sha256_update(&ctx, key, klen);
	sha256_sum(&ctx, md);

	/* A = sha(key salt repeat-B alternate-B-key) */
	sha256_init(&ctx);
	sha256_update(&ctx, key, klen);
	sha256_update(&ctx, salt, slen);
	hashmd(&ctx, klen, md);
	for (i = klen; i > 0; i >>= 1)
		if (i & 1)
			sha256_update(&ctx, md, sizeof md);
		else
			sha256_update(&ctx, key, klen);
	sha256_sum(&ctx, md);

	/* DP = sha(repeat-key), this step takes O(klen^2) time */
	sha256_init(&ctx);
	for (i = 0; i < klen; i++)
		sha256_update(&ctx, key, klen);
	sha256_sum(&ctx, kmd);

	/* DS = sha(repeat-salt) */
	sha256_init(&ctx);
	for (i = 0; i < 16 + md[0]; i++)
		sha256_update(&ctx, salt, slen);
	sha256_sum(&ctx, smd);

	/* iterate A = f(A,DP,DS), this step takes O(rounds*klen) time */
	for (i = 0; i < r; i++) {
		sha256_init(&ctx);
		if (i % 2)
			hashmd(&ctx, klen, kmd);
		else
			sha256_update(&ctx, md, sizeof md);
		if (i % 3)
			sha256_update(&ctx, smd, slen);
		if (i % 7)
			hashmd(&ctx, klen, kmd);
		if (i % 2)
			sha256_update(&ctx, md, sizeof md);
		else
			hashmd(&ctx, klen, kmd);
		sha256_sum(&ctx, md);
	}

	/* output is $5$rounds=n$salt$hash */
	p = output;
	p += sprintf(p, "$5$%s%.*s$", rounds, slen, salt);
	static const unsigned char perm[][3] = {
		0,10,20,21,1,11,12,22,2,3,13,23,24,4,14,
		15,25,5,6,16,26,27,7,17,18,28,8,9,19,29 };
	for (i=0; i<10; i++) p = to64(p,
		(md[perm[i][0]]<<16)|(md[perm[i][1]]<<8)|md[perm[i][2]], 4);
	p = to64(p, (md[31]<<8)|md[30], 3);
	*p = 0;
	return output;
}