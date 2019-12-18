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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  PWBLOCK_LEN ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc4_skip (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ utf8_to_ucs2 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int,size_t*) ; 

int encrypt_pw_block_with_password_hash(
	const u8 *password, size_t password_len,
	const u8 *password_hash, u8 *pw_block)
{
	size_t ucs2_len, offset;
	u8 *pos;

	os_memset(pw_block, 0, PWBLOCK_LEN);

	if (utf8_to_ucs2(password, password_len, pw_block, 512, &ucs2_len) < 0)
		return -1;

	if (ucs2_len > 256)
		return -1;

	offset = (256 - ucs2_len) * 2;
	if (offset != 0) {
		os_memmove(pw_block + offset, pw_block, ucs2_len * 2);
		if (os_get_random(pw_block, offset) < 0)
			return -1;
	}
	/*
	 * PasswordLength is 4 octets, but since the maximum password length is
	 * 256, only first two (in little endian byte order) can be non-zero.
	 */
	pos = &pw_block[2 * 256];
	WPA_PUT_LE16(pos, password_len * 2);
	rc4_skip(password_hash, 16, 0, pw_block, PWBLOCK_LEN);
	return 0;
}