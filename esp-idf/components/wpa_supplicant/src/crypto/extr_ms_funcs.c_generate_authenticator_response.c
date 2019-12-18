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
 int generate_authenticator_response_pwhash (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ nt_password_hash (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

int generate_authenticator_response(const u8 *password, size_t password_len,
				const u8 *peer_challenge,
				const u8 *auth_challenge,
				const u8 *username, size_t username_len,
				const u8 *nt_response, u8 *response)
{
	u8 password_hash[16];
	if (nt_password_hash(password, password_len, password_hash))
		return -1;
	return generate_authenticator_response_pwhash(
		password_hash, peer_challenge, auth_challenge,
		username, username_len, nt_response, response);
}