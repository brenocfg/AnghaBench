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
struct sha512 {int dummy; } ;

/* Variables and functions */
 unsigned int KEY_MAX ; 
 unsigned int ROUNDS_DEFAULT ; 
 unsigned long ROUNDS_MAX ; 
 unsigned long ROUNDS_MIN ; 
 unsigned int SALT_MAX ; 
 int /*<<< orphan*/  hashmd (struct sha512*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  sha512_init (struct sha512*) ; 
 int /*<<< orphan*/  sha512_sum (struct sha512*,unsigned char*) ; 
 int /*<<< orphan*/  sha512_update (struct sha512*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 char* to64 (char*,unsigned char,int) ; 

__attribute__((used)) static char *sha512crypt(const char *key, const char *setting, char *output)
{
	struct sha512 ctx;
	unsigned char md[64], kmd[64], smd[64];
	unsigned int i, r, klen, slen;
	char rounds[20] = "";
	const char *salt;
	char *p;

	/* reject large keys */
	for (i = 0; i <= KEY_MAX && key[i]; i++);
	if (i > KEY_MAX)
		return 0;
	klen = i;

	/* setting: $6$rounds=n$salt$ (rounds=n$ and closing $ are optional) */
	if (strncmp(setting, "$6$", 3) != 0)
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
	sha512_init(&ctx);
	sha512_update(&ctx, key, klen);
	sha512_update(&ctx, salt, slen);
	sha512_update(&ctx, key, klen);
	sha512_sum(&ctx, md);

	/* A = sha(key salt repeat-B alternate-B-key) */
	sha512_init(&ctx);
	sha512_update(&ctx, key, klen);
	sha512_update(&ctx, salt, slen);
	hashmd(&ctx, klen, md);
	for (i = klen; i > 0; i >>= 1)
		if (i & 1)
			sha512_update(&ctx, md, sizeof md);
		else
			sha512_update(&ctx, key, klen);
	sha512_sum(&ctx, md);

	/* DP = sha(repeat-key), this step takes O(klen^2) time */
	sha512_init(&ctx);
	for (i = 0; i < klen; i++)
		sha512_update(&ctx, key, klen);
	sha512_sum(&ctx, kmd);

	/* DS = sha(repeat-salt) */
	sha512_init(&ctx);
	for (i = 0; i < 16 + md[0]; i++)
		sha512_update(&ctx, salt, slen);
	sha512_sum(&ctx, smd);

	/* iterate A = f(A,DP,DS), this step takes O(rounds*klen) time */
	for (i = 0; i < r; i++) {
		sha512_init(&ctx);
		if (i % 2)
			hashmd(&ctx, klen, kmd);
		else
			sha512_update(&ctx, md, sizeof md);
		if (i % 3)
			sha512_update(&ctx, smd, slen);
		if (i % 7)
			hashmd(&ctx, klen, kmd);
		if (i % 2)
			sha512_update(&ctx, md, sizeof md);
		else
			hashmd(&ctx, klen, kmd);
		sha512_sum(&ctx, md);
	}

	/* output is $6$rounds=n$salt$hash */
	p = output;
	p += sprintf(p, "$6$%s%.*s$", rounds, slen, salt);
#if 1
	static const unsigned char perm[][3] = {
		0,21,42,22,43,1,44,2,23,3,24,45,25,46,4,
		47,5,26,6,27,48,28,49,7,50,8,29,9,30,51,
		31,52,10,53,11,32,12,33,54,34,55,13,56,14,35,
		15,36,57,37,58,16,59,17,38,18,39,60,40,61,19,
		62,20,41 };
	for (i=0; i<21; i++) p = to64(p,
		(md[perm[i][0]]<<16)|(md[perm[i][1]]<<8)|md[perm[i][2]], 4);
#else
	p = to64(p, (md[0]<<16)|(md[21]<<8)|md[42], 4);
	p = to64(p, (md[22]<<16)|(md[43]<<8)|md[1], 4);
	p = to64(p, (md[44]<<16)|(md[2]<<8)|md[23], 4);
	p = to64(p, (md[3]<<16)|(md[24]<<8)|md[45], 4);
	p = to64(p, (md[25]<<16)|(md[46]<<8)|md[4], 4);
	p = to64(p, (md[47]<<16)|(md[5]<<8)|md[26], 4);
	p = to64(p, (md[6]<<16)|(md[27]<<8)|md[48], 4);
	p = to64(p, (md[28]<<16)|(md[49]<<8)|md[7], 4);
	p = to64(p, (md[50]<<16)|(md[8]<<8)|md[29], 4);
	p = to64(p, (md[9]<<16)|(md[30]<<8)|md[51], 4);
	p = to64(p, (md[31]<<16)|(md[52]<<8)|md[10], 4);
	p = to64(p, (md[53]<<16)|(md[11]<<8)|md[32], 4);
	p = to64(p, (md[12]<<16)|(md[33]<<8)|md[54], 4);
	p = to64(p, (md[34]<<16)|(md[55]<<8)|md[13], 4);
	p = to64(p, (md[56]<<16)|(md[14]<<8)|md[35], 4);
	p = to64(p, (md[15]<<16)|(md[36]<<8)|md[57], 4);
	p = to64(p, (md[37]<<16)|(md[58]<<8)|md[16], 4);
	p = to64(p, (md[59]<<16)|(md[17]<<8)|md[38], 4);
	p = to64(p, (md[18]<<16)|(md[39]<<8)|md[60], 4);
	p = to64(p, (md[40]<<16)|(md[61]<<8)|md[19], 4);
	p = to64(p, (md[62]<<16)|(md[20]<<8)|md[41], 4);
#endif
	p = to64(p, md[63], 2);
	*p = 0;
	return output;
}