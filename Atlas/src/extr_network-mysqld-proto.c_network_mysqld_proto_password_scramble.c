#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int guchar ;
typedef  int gsize ;
struct TYPE_7__ {int* str; int len; int allocated_len; } ;
typedef  TYPE_1__ GString ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_type_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_set_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_password_hash (TYPE_1__*,char const*,int) ; 

int network_mysqld_proto_password_scramble(GString *response,
		const char *challenge, gsize challenge_len,
		const char *hashed_password, gsize hashed_password_len) {
	int i;
	GChecksum *cs;
	GString *step2;

	g_return_val_if_fail(NULL != challenge, -1);
	g_return_val_if_fail(20 == challenge_len, -1);
	g_return_val_if_fail(NULL != hashed_password, -1);
	g_return_val_if_fail(20 == hashed_password_len, -1);

	/**
	 * we have to run
	 *
	 *   XOR( SHA1(password), SHA1(challenge + SHA1(SHA1(password)))
	 *
	 * where SHA1(password) is the hashed_password and
	 *       challenge      is ... challenge
	 *
	 *   XOR( hashed_password, SHA1(challenge + SHA1(hashed_password)))
	 *
	 */

	/* 1. SHA1(hashed_password) */
	step2 = g_string_new(NULL);
	network_mysqld_proto_password_hash(step2, hashed_password, hashed_password_len);

	/* 2. SHA1(challenge + SHA1(hashed_password) */
	cs = g_checksum_new(G_CHECKSUM_SHA1);
	g_checksum_update(cs, (guchar *)challenge, challenge_len);
	g_checksum_update(cs, (guchar *)step2->str, step2->len);
	
	g_string_set_size(response, g_checksum_type_get_length(G_CHECKSUM_SHA1));
	response->len = response->allocated_len;
	g_checksum_get_digest(cs, (guchar *)response->str, &(response->len));
	
	g_checksum_free(cs);

	/* XOR the hashed_password with SHA1(challenge + SHA1(hashed_password)) */
	for (i = 0; i < 20; i++) {
		response->str[i] = (guchar)response->str[i] ^ (guchar)hashed_password[i];
	}

	g_string_free(step2, TRUE);

	return 0;
}