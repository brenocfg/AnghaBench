#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct SslClientCertInfo {char* PreverifyErrMessage; TYPE_1__* X; int /*<<< orphan*/  PreverifyErr; } ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {int do_not_free; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 TYPE_1__* CloneX (TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (char*,char const*) ; 
 int /*<<< orphan*/  FreeX (TYPE_1__*) ; 
 int /*<<< orphan*/  GetSslClientCertIndex () ; 
 int /*<<< orphan*/  PREVERIFY_ERR_MESSAGE_SIZE ; 
 struct SslClientCertInfo* SSL_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_ex_data_X509_STORE_CTX_idx () ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* X509ToX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get0_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* X509_verify_cert_error_string (int /*<<< orphan*/ ) ; 

int SslCertVerifyCallback(int preverify_ok, X509_STORE_CTX *ctx)
{
	SSL *ssl;
	struct SslClientCertInfo *clientcert;
	X509 *cert;

	ssl = X509_STORE_CTX_get_ex_data(ctx, SSL_get_ex_data_X509_STORE_CTX_idx());
	clientcert = SSL_get_ex_data(ssl, GetSslClientCertIndex());

	if (clientcert != NULL)
	{
		clientcert->PreverifyErr = X509_STORE_CTX_get_error(ctx);
		clientcert->PreverifyErrMessage[0] = '\0';
		if (!preverify_ok)
		{
			const char *msg = X509_verify_cert_error_string(clientcert->PreverifyErr);
			StrCpy(clientcert->PreverifyErrMessage, PREVERIFY_ERR_MESSAGE_SIZE, (char *)msg);
			Debug("SslCertVerifyCallback preverify error: '%s'\n", msg);
		}
		else
		{
			cert = X509_STORE_CTX_get0_cert(ctx);
			if (cert != NULL)
			{
				X *tmpX = X509ToX(cert); // this only wraps cert, but we need to make a copy
				X *copyX = CloneX(tmpX);
				tmpX->do_not_free = true; // do not release inner X509 object
				FreeX(tmpX);
				clientcert->X = copyX;
			}
		}
	}

	return 1; /* allow the verification process to continue */
}