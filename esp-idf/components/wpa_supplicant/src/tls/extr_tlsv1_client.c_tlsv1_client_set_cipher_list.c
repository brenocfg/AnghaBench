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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tlsv1_client {size_t num_cipher_suites; int /*<<< orphan*/ * cipher_suites; } ;

/* Variables and functions */
 scalar_t__ TLS_CIPHER_ANON_DH_AES128_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_3DES_EDE_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_128_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_128_CBC_SHA256 ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_256_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_AES_256_CBC_SHA256 ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_DES_CBC_SHA ; 
 int /*<<< orphan*/  TLS_DH_anon_WITH_RC4_128_MD5 ; 

int tlsv1_client_set_cipher_list(struct tlsv1_client *conn, u8 *ciphers)
{
	size_t count;
	u16 *suites;

	/* TODO: implement proper configuration of cipher suites */
	if (ciphers[0] == TLS_CIPHER_ANON_DH_AES128_SHA) {
		count = 0;
		suites = conn->cipher_suites;
		suites[count++] = TLS_DH_anon_WITH_AES_256_CBC_SHA256;
		suites[count++] = TLS_DH_anon_WITH_AES_256_CBC_SHA;
		suites[count++] = TLS_DH_anon_WITH_AES_128_CBC_SHA256;
		suites[count++] = TLS_DH_anon_WITH_AES_128_CBC_SHA;
#ifdef CONFIG_DES3
		suites[count++] = TLS_DH_anon_WITH_3DES_EDE_CBC_SHA;
#endif
		suites[count++] = TLS_DH_anon_WITH_RC4_128_MD5;
#ifdef CONFIG_DES
		suites[count++] = TLS_DH_anon_WITH_DES_CBC_SHA;
#endif

		/*
		 * Cisco AP (at least 350 and 1200 series) local authentication
		 * server does not know how to search cipher suites from the
		 * list and seem to require that the last entry in the list is
		 * the one that it wants to use. However, TLS specification
		 * requires the list to be in the client preference order. As a
		 * workaround, add anon-DH AES-128-SHA1 again at the end of the
		 * list to allow the Cisco code to find it.
		 */
		suites[count++] = TLS_DH_anon_WITH_AES_128_CBC_SHA;
		conn->num_cipher_suites = count;
	}

	return 0;
}