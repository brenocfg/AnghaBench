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
struct x509_certificate {struct x509_certificate* sign_value; struct x509_certificate* public_key; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (struct x509_certificate*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct x509_certificate*,scalar_t__) ; 
 int /*<<< orphan*/  x509_free_name (int /*<<< orphan*/ *) ; 

void x509_certificate_free(struct x509_certificate *cert)
{
	if (cert == NULL)
		return;
	if (cert->next) {
		wpa_printf(MSG_DEBUG, "X509: x509_certificate_free: cer=%p "
			   "was still on a list (next=%p)\n",
			   cert, cert->next);
	}
	x509_free_name(&cert->issuer);
	x509_free_name(&cert->subject);
	os_free(cert->public_key);
	os_free(cert->sign_value);
	os_free(cert);
}