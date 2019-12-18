#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;
typedef  int /*<<< orphan*/  mbedtls_md5_context ;
struct TYPE_4__ {int /*<<< orphan*/  fin_sha1; int /*<<< orphan*/  fin_md5; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_BUF (int,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  mbedtls_md5_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md5_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 

void ssl_calc_verify_tls( mbedtls_ssl_context *ssl, unsigned char hash[36] )
{
    mbedtls_md5_context md5;
    mbedtls_sha1_context sha1;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> calc verify tls" ) );

    mbedtls_md5_init( &md5 );
    mbedtls_sha1_init( &sha1 );

    mbedtls_md5_clone( &md5, &ssl->handshake->fin_md5 );
    mbedtls_sha1_clone( &sha1, &ssl->handshake->fin_sha1 );

     mbedtls_md5_finish( &md5,  hash );
    mbedtls_sha1_finish( &sha1, hash + 16 );

    MBEDTLS_SSL_DEBUG_BUF( 3, "calculated verify result", hash, 36 );
    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= calc verify" ) );

    mbedtls_md5_free(  &md5  );
    mbedtls_sha1_free( &sha1 );

    return;
}