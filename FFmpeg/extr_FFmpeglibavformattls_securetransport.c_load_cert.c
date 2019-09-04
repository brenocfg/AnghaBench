#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_6__ {int /*<<< orphan*/  key_file; int /*<<< orphan*/  cert_file; } ;
struct TYPE_8__ {int /*<<< orphan*/  ssl_context; TYPE_1__ tls_shared; } ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  SecKeyRef ;
typedef  int /*<<< orphan*/ * SecIdentityRef ;
typedef  int /*<<< orphan*/  SecCertificateRef ;
typedef  int /*<<< orphan*/ * CFMutableArrayRef ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/ * CFArrayCreateMutableCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CFArrayGetValueAtIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArraySetValueAtIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SSLSetCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SecIdentityCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int import_pem (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 

__attribute__((used)) static int load_cert(URLContext *h)
{
    TLSContext *c = h->priv_data;
    int ret = 0;
    CFArrayRef certArray = NULL;
    CFArrayRef keyArray = NULL;
    SecIdentityRef id = NULL;
    CFMutableArrayRef outArray = NULL;

    if ((ret = import_pem(h, c->tls_shared.cert_file, &certArray)) < 0)
        goto end;

    if ((ret = import_pem(h, c->tls_shared.key_file, &keyArray)) < 0)
        goto end;

    if (!(id = SecIdentityCreate(kCFAllocatorDefault,
                                 (SecCertificateRef)CFArrayGetValueAtIndex(certArray, 0),
                                 (SecKeyRef)CFArrayGetValueAtIndex(keyArray, 0)))) {
        ret = AVERROR_UNKNOWN;
        goto end;
    }

    if (!(outArray = CFArrayCreateMutableCopy(kCFAllocatorDefault, 0, certArray))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    CFArraySetValueAtIndex(outArray, 0, id);

    SSLSetCertificate(c->ssl_context, outArray);

end:
    if (certArray)
        CFRelease(certArray);
    if (keyArray)
        CFRelease(keyArray);
    if (outArray)
        CFRelease(outArray);
    if (id)
        CFRelease(id);
    return ret;
}