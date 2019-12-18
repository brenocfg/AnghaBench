#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int guchar ;
typedef  int gsize ;
struct TYPE_4__ {int* str; int /*<<< orphan*/  len; int /*<<< orphan*/  allocated_len; } ;
typedef  TYPE_1__ GString ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_type_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_set_size (TYPE_1__*,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_password_unscramble(
		GString *hashed_password,
		const char *challenge, gsize challenge_len,
		const char *response, gsize response_len,
		const char *double_hashed, gsize double_hashed_len) {
	int i;
	GChecksum *cs;

	g_return_val_if_fail(NULL != response, FALSE);
	g_return_val_if_fail(20 == response_len, FALSE);
	g_return_val_if_fail(NULL != challenge, FALSE);
	g_return_val_if_fail(20 == challenge_len, FALSE);
	g_return_val_if_fail(NULL != double_hashed, FALSE);
	g_return_val_if_fail(20 == double_hashed_len, FALSE);

	/**
	 * to check we have to:
	 *
	 *   hashed_password = XOR( response, SHA1(challenge + double_hashed))
	 *   double_hashed == SHA1(hashed_password)
	 *
	 * where SHA1(password) is the hashed_password and
	 *       challenge      is ... challenge
	 *       response       is the response of the client
	 *
	 *   XOR( hashed_password, SHA1(challenge + SHA1(hashed_password)))
	 *
	 */


	/* 1. SHA1(challenge + double_hashed) */
	cs = g_checksum_new(G_CHECKSUM_SHA1);
	g_checksum_update(cs, (guchar *)challenge, challenge_len);
	g_checksum_update(cs, (guchar *)double_hashed, double_hashed_len);
	
	g_string_set_size(hashed_password, g_checksum_type_get_length(G_CHECKSUM_SHA1));
	hashed_password->len = hashed_password->allocated_len;
	g_checksum_get_digest(cs, (guchar *)hashed_password->str, &(hashed_password->len));
	
	g_checksum_free(cs);
	
	/* 2. XOR the response with SHA1(challenge + SHA1(hashed_password)) */
	for (i = 0; i < 20; i++) {
		hashed_password->str[i] = (guchar)response[i] ^ (guchar)hashed_password->str[i];
	}

	return 0;
}