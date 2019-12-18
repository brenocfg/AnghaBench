#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/ * key; int /*<<< orphan*/ * cert; } ;
typedef  TYPE_1__ mbedtls_ssl_key_cert ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 scalar_t__ mbedtls_calloc (int,int) ; 

__attribute__((used)) static int ssl_append_key_cert( mbedtls_ssl_key_cert **head,
                                mbedtls_x509_crt *cert,
                                mbedtls_pk_context *key )
{
    mbedtls_ssl_key_cert *keycert = (mbedtls_ssl_key_cert*)
       mbedtls_calloc( 1, sizeof( mbedtls_ssl_key_cert ) );
    if( keycert == NULL )
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );

    keycert->cert = cert;
    keycert->key  = key;
    keycert->next = NULL;

    /* Update head is the list was null, else add to the end */
    if( *head == NULL )
    {
        *head = keycert;
    }
    else
    {
        mbedtls_ssl_key_cert *cur = *head;
        while( cur->next != NULL )
            cur = cur->next;
        cur->next = keycert;
    }

    return( 0 );
}