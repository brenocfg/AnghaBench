#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_8__ {int /*<<< orphan*/ * cert; } ;
typedef  TYPE_3__ mbedtls_ssl_key_cert ;
struct TYPE_9__ {TYPE_2__* conf; TYPE_1__* handshake; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_7__ {TYPE_3__* key_cert; } ;
struct TYPE_6__ {TYPE_3__* key_cert; } ;

/* Variables and functions */

__attribute__((used)) static inline mbedtls_x509_crt *mbedtls_ssl_own_cert( mbedtls_ssl_context *ssl )
{
    mbedtls_ssl_key_cert *key_cert;

    if( ssl->handshake != NULL && ssl->handshake->key_cert != NULL )
        key_cert = ssl->handshake->key_cert;
    else
        key_cert = ssl->conf->key_cert;

    return( key_cert == NULL ? NULL : key_cert->cert );
}