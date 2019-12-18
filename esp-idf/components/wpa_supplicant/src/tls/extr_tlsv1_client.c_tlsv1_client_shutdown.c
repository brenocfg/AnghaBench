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
struct tlsv1_client {scalar_t__ session_resumed; int /*<<< orphan*/ * server_rsa_key; scalar_t__ certificate_requested; int /*<<< orphan*/  rl; int /*<<< orphan*/  verify; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_HELLO ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_NULL_WITH_NULL_NULL ; 
 int /*<<< orphan*/  crypto_public_key_free (int /*<<< orphan*/ *) ; 
 scalar_t__ tls_verify_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_change_read_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_change_write_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlsv1_record_set_cipher_suite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tlsv1_client_shutdown(struct tlsv1_client *conn)
{
	conn->state = CLIENT_HELLO;

	if (tls_verify_hash_init(&conn->verify) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to re-initialize verify "
			   "hash");
		return -1;
	}

	tlsv1_record_set_cipher_suite(&conn->rl, TLS_NULL_WITH_NULL_NULL);
	tlsv1_record_change_write_cipher(&conn->rl);
	tlsv1_record_change_read_cipher(&conn->rl);

	conn->certificate_requested = 0;
	crypto_public_key_free(conn->server_rsa_key);
	conn->server_rsa_key = NULL;
	conn->session_resumed = 0;

	return 0;
}