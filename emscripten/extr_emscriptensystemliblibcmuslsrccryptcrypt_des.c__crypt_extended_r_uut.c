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
typedef  size_t uint32_t ;
struct expanded_key {int dummy; } ;
typedef  int /*<<< orphan*/  keybuf ;

/* Variables and functions */
 unsigned char const _PASSWORD_EFMT1 ; 
 int /*<<< orphan*/  __des_setkey (unsigned char*,struct expanded_key*) ; 
 int /*<<< orphan*/  __do_des (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*,size_t,int /*<<< orphan*/ ,struct expanded_key*) ; 
 unsigned char const* ascii64 ; 
 scalar_t__ ascii_is_unsafe (unsigned char const) ; 
 int ascii_to_bin (unsigned char const) ; 
 int /*<<< orphan*/  des_cipher (unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,struct expanded_key*) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  setup_salt (size_t) ; 

__attribute__((used)) static char *_crypt_extended_r_uut(const char *_key, const char *_setting, char *output)
{
	const unsigned char *key = (const unsigned char *)_key;
	const unsigned char *setting = (const unsigned char *)_setting;
	struct expanded_key ekey;
	unsigned char keybuf[8];
	unsigned char *p, *q;
	uint32_t count, salt, l, r0, r1;
	unsigned int i;

	/*
	 * Copy the key, shifting each character left by one bit and padding
	 * with zeroes.
	 */
	q = keybuf;
	while (q <= &keybuf[sizeof(keybuf) - 1]) {
		*q++ = *key << 1;
		if (*key)
			key++;
	}
	__des_setkey(keybuf, &ekey);

	if (*setting == _PASSWORD_EFMT1) {
		/*
		 * "new"-style:
		 *	setting - underscore, 4 chars of count, 4 chars of salt
		 *	key - unlimited characters
		 */
		for (i = 1, count = 0; i < 5; i++) {
			uint32_t value = ascii_to_bin(setting[i]);
			if (ascii64[value] != setting[i])
				return NULL;
			count |= value << (i - 1) * 6;
		}
		if (!count)
			return NULL;

		for (i = 5, salt = 0; i < 9; i++) {
			uint32_t value = ascii_to_bin(setting[i]);
			if (ascii64[value] != setting[i])
				return NULL;
			salt |= value << (i - 5) * 6;
		}

		while (*key) {
			/*
			 * Encrypt the key with itself.
			 */
			des_cipher(keybuf, keybuf, 1, 0, &ekey);
			/*
			 * And XOR with the next 8 characters of the key.
			 */
			q = keybuf;
			while (q <= &keybuf[sizeof(keybuf) - 1] && *key)
				*q++ ^= *key++ << 1;
			__des_setkey(keybuf, &ekey);
		}

		memcpy(output, setting, 9);
		output[9] = '\0';
		p = (unsigned char *)output + 9;
	} else {
		/*
		 * "old"-style:
		 *	setting - 2 chars of salt
		 *	key - up to 8 characters
		 */
		count = 25;

		if (ascii_is_unsafe(setting[0]) || ascii_is_unsafe(setting[1]))
			return NULL;

		salt = (ascii_to_bin(setting[1]) << 6)
		     |  ascii_to_bin(setting[0]);

		output[0] = setting[0];
		output[1] = setting[1];
		p = (unsigned char *)output + 2;
	}

	/*
	 * Do it.
	 */
	__do_des(0, 0, &r0, &r1, count, setup_salt(salt), &ekey);

	/*
	 * Now encode the result...
	 */
	l = (r0 >> 8);
	*p++ = ascii64[(l >> 18) & 0x3f];
	*p++ = ascii64[(l >> 12) & 0x3f];
	*p++ = ascii64[(l >> 6) & 0x3f];
	*p++ = ascii64[l & 0x3f];

	l = (r0 << 16) | ((r1 >> 16) & 0xffff);
	*p++ = ascii64[(l >> 18) & 0x3f];
	*p++ = ascii64[(l >> 12) & 0x3f];
	*p++ = ascii64[(l >> 6) & 0x3f];
	*p++ = ascii64[l & 0x3f];

	l = r1 << 2;
	*p++ = ascii64[(l >> 12) & 0x3f];
	*p++ = ascii64[(l >> 6) & 0x3f];
	*p++ = ascii64[l & 0x3f];
	*p = 0;

	return output;
}