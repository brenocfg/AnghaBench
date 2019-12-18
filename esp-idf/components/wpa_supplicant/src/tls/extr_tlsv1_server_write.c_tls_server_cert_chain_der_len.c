#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x509_certificate {int /*<<< orphan*/  issuer; scalar_t__ cert_len; } ;
struct tlsv1_server {TYPE_1__* cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  trusted_certs; struct x509_certificate* cert; } ;

/* Variables and functions */
 struct x509_certificate* x509_certificate_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ x509_certificate_self_signed (struct x509_certificate*) ; 

__attribute__((used)) static size_t tls_server_cert_chain_der_len(struct tlsv1_server *conn)
{
	size_t len = 0;
	struct x509_certificate *cert;

	cert = conn->cred->cert;
	while (cert) {
		len += 3 + cert->cert_len;
		if (x509_certificate_self_signed(cert))
			break;
		cert = x509_certificate_get_subject(conn->cred->trusted_certs,
						    &cert->issuer);
	}

	return len;
}