#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  alt_dns ;
struct TYPE_13__ {int size; char* data; } ;
typedef  TYPE_1__ X_SERIAL ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_14__ {int /*<<< orphan*/  x509; } ;
typedef  TYPE_2__ X ;
typedef  int UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_17__ {int length; void* data; } ;
struct TYPE_16__ {int private_key; int /*<<< orphan*/  pkey; } ;
struct TYPE_15__ {int /*<<< orphan*/  CommonName; } ;
typedef  TYPE_3__ NAME ;
typedef  TYPE_4__ K ;
typedef  int /*<<< orphan*/  ASN1_TIME ;
typedef  TYPE_5__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,char*,int) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeX509 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX509Name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int /*<<< orphan*/ * NameToX509Name (TYPE_3__*) ; 
 int /*<<< orphan*/ * NewBasicKeyUsageForX509 () ; 
 int /*<<< orphan*/ * NewExtendedKeyUsageForX509 () ; 
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 void* OPENSSL_malloc (int) ; 
 int SystemTime64 () ; 
 int /*<<< orphan*/  UINT64ToAsn1Time (void*,int) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509V3_EXT_conf_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_add_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * X509_get0_notAfter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_notBefore (int /*<<< orphan*/ *) ; 
 TYPE_5__* X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_new () ; 
 int /*<<< orphan*/  X509_set_issuer_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_set_subject_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_version (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  X509_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_lock ; 

X509 *NewX509(K *pub, K *priv, X *ca, NAME *name, UINT days, X_SERIAL *serial)
{
	X509 *x509;
	UINT64 notBefore, notAfter;
	const ASN1_TIME *t1, *t2;
	X509_NAME *subject_name, *issuer_name;
	X509_EXTENSION *ex = NULL;
	X509_EXTENSION *eku = NULL;
	X509_EXTENSION *busage = NULL;
	ASN1_INTEGER *s;
	// Validate arguments
	if (pub == NULL || name == NULL || ca == NULL)
	{
		return NULL;
	}
	if (pub->private_key != false)
	{
		return NULL;
	}
	if (priv->private_key == false)
	{
		return NULL;
	}

	notBefore = SystemTime64();
	notAfter = notBefore + (UINT64)days * (UINT64)3600 * (UINT64)24 * (UINT64)1000;

	// Creating a X509
	x509 = X509_new();
	if (x509 == NULL)
	{
		return NULL;
	}

	// Make it a v3 certificate
	X509_set_version(x509, 2L);

	// Set the Expiration
	t1 = X509_get0_notBefore(x509);
	t2 = X509_get0_notAfter(x509);
	if (!UINT64ToAsn1Time((void *)t1, notBefore))
	{
		FreeX509(x509);
		return NULL;
	}
	if (!UINT64ToAsn1Time((void *)t2, notAfter))
	{
		FreeX509(x509);
		return NULL;
	}

	// Set the name
	subject_name = NameToX509Name(name);
	if (subject_name == NULL)
	{
		FreeX509(x509);
		return NULL;
	}
	issuer_name = X509_get_subject_name(ca->x509);
	if (issuer_name == NULL)
	{
		FreeX509Name(subject_name);
		FreeX509(x509);
		return NULL;
	}

	X509_set_issuer_name(x509, issuer_name);
	X509_set_subject_name(x509, subject_name);

	FreeX509Name(subject_name);

	// Set the Serial Number
	s = X509_get_serialNumber(x509);
	OPENSSL_free(s->data);
	if (serial == NULL)
	{
		char zero = 0;
		s->data = OPENSSL_malloc(sizeof(char));
		Copy(s->data, &zero, sizeof(char));
		s->length = sizeof(char);
	}
	else
	{
		s->data = OPENSSL_malloc(serial->size);
		Copy(s->data, serial->data, serial->size);
		s->length = serial->size;
	}

	/*
	// Extensions
	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_basic_constraints,	"critical,CA:TRUE");
	X509_add_ext(x509, ex, -1);
	X509_EXTENSION_free(ex);
*/

	// Basic usage
	busage = NewBasicKeyUsageForX509();
	if (busage != NULL)
	{
		X509_add_ext(x509, busage, -1);
		X509_EXTENSION_free(busage);
	}

	// EKU
	eku = NewExtendedKeyUsageForX509();
	if (eku != NULL)
	{
		X509_add_ext(x509, eku, -1);
		X509_EXTENSION_free(eku);
	}

	// Alternative subject name
	if (UniIsEmptyStr(name->CommonName) == false)
	{
		char alt_dns[MAX_PATH];

		Format(alt_dns, sizeof(alt_dns), "DNS.1:%S", name->CommonName);

		ex = X509V3_EXT_conf_nid(NULL, NULL, NID_subject_alt_name,	alt_dns);
		X509_add_ext(x509, ex, -1);
		X509_EXTENSION_free(ex);
	}

	Lock(openssl_lock);
	{
		// Set the public key
		X509_set_pubkey(x509, pub->pkey);

		// Signature
		// 2014.3.19 set the initial digest algorithm to SHA-256
		X509_sign(x509, priv->pkey, EVP_sha256());
	}
	Unlock(openssl_lock);

	return x509;
}