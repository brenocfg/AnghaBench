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
struct TYPE_6__ {int /*<<< orphan*/  session; int /*<<< orphan*/  cert; int /*<<< orphan*/  client_CA; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT3 (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_METHOD_CALL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 

void SSL_free(SSL *ssl)
{
    SSL_ASSERT3(ssl);

    SSL_METHOD_CALL(free, ssl);

    X509_free(ssl->client_CA);

    ssl_cert_free(ssl->cert);

    SSL_SESSION_free(ssl->session);

    ssl_mem_free(ssl);
}