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
 scalar_t__ encrypt_pw_block_with_password_hash (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nt_password_hash (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

int new_password_encrypted_with_old_nt_password_hash(
	const u8 *new_password, size_t new_password_len,
	const u8 *old_password, size_t old_password_len,
	u8 *encrypted_pw_block)
{
	u8 password_hash[16];

	if (nt_password_hash(old_password, old_password_len, password_hash))
		return -1;
	if (encrypt_pw_block_with_password_hash(new_password, new_password_len,
						password_hash,
						encrypted_pw_block))
		return -1;
	return 0;
}