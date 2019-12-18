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
typedef  int /*<<< orphan*/  tls_cipher ;
struct tls_cipher_suite {int key_exchange; } ;

/* Variables and functions */
#define  TLS_KEY_X_DHE_DSS 134 
#define  TLS_KEY_X_DHE_DSS_EXPORT 133 
#define  TLS_KEY_X_DHE_RSA 132 
#define  TLS_KEY_X_DHE_RSA_EXPORT 131 
#define  TLS_KEY_X_DH_anon 130 
#define  TLS_KEY_X_DH_anon_EXPORT 129 
#define  TLS_KEY_X_RSA_EXPORT 128 
 struct tls_cipher_suite* tls_get_cipher_suite (int /*<<< orphan*/ ) ; 

int tls_server_key_exchange_allowed(tls_cipher cipher)
{
	const struct tls_cipher_suite *suite;

	/* RFC 2246, Section 7.4.3 */
	suite = tls_get_cipher_suite(cipher);
	if (suite == NULL)
		return 0;

	switch (suite->key_exchange) {
	case TLS_KEY_X_DHE_DSS:
	case TLS_KEY_X_DHE_DSS_EXPORT:
	case TLS_KEY_X_DHE_RSA:
	case TLS_KEY_X_DHE_RSA_EXPORT:
	case TLS_KEY_X_DH_anon_EXPORT:
	case TLS_KEY_X_DH_anon:
		return 1;
	case TLS_KEY_X_RSA_EXPORT:
		return 1 /* FIX: public key len > 512 bits */;
	default:
		return 0;
	}
}