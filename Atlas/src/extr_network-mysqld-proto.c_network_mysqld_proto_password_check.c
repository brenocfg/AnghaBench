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
typedef  int gsize ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_password_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_password_unscramble (int /*<<< orphan*/ *,char const*,int,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  strleq (int /*<<< orphan*/ ,char const*,int) ; 

gboolean network_mysqld_proto_password_check(
		const char *challenge, gsize challenge_len,
		const char *response, gsize response_len,
		const char *double_hashed, gsize double_hashed_len) {

	GString *hashed_password, *step2;
	gboolean is_same;

	g_return_val_if_fail(NULL != response, FALSE);
	g_return_val_if_fail(20 == response_len, FALSE);
	g_return_val_if_fail(NULL != challenge, FALSE);
	g_return_val_if_fail(20 == challenge_len, FALSE);
	g_return_val_if_fail(NULL != double_hashed, FALSE);
	g_return_val_if_fail(20 == double_hashed_len, FALSE);

	hashed_password = g_string_new(NULL);

	network_mysqld_proto_password_unscramble(hashed_password, 
			challenge, challenge_len,
			response, response_len,
			double_hashed, double_hashed_len);

	/* 3. SHA1(hashed_password) */
	step2 = g_string_new(NULL);
	network_mysqld_proto_password_hash(step2, S(hashed_password));
	
	/* 4. the result of 3 should be the same what we got from the mysql.user table */
	is_same = strleq(S(step2), double_hashed, double_hashed_len);

	g_string_free(step2, TRUE);
	g_string_free(hashed_password, TRUE);

	return is_same;
}