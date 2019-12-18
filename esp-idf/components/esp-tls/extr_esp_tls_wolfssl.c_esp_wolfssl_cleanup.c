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
struct TYPE_3__ {scalar_t__ priv_ctx; scalar_t__ priv_ssl; } ;
typedef  TYPE_1__ esp_tls_t ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int /*<<< orphan*/  wolfSSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_Cleanup () ; 
 int /*<<< orphan*/  wolfSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_shutdown (int /*<<< orphan*/ *) ; 

void esp_wolfssl_cleanup(esp_tls_t *tls)
{
    if (!tls) {
        return;
    }
    wolfSSL_shutdown( (WOLFSSL *)tls->priv_ssl);
    wolfSSL_free( (WOLFSSL *)tls->priv_ssl);
    wolfSSL_CTX_free( (WOLFSSL_CTX *)tls->priv_ctx);
    wolfSSL_Cleanup();
}