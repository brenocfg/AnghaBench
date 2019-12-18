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
struct ssl_pm {int /*<<< orphan*/  ssl; int /*<<< orphan*/  conf; int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ssl_pm; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (struct ssl_pm*) ; 

void ssl_pm_free(SSL *ssl)
{
    struct ssl_pm *ssl_pm = (struct ssl_pm *)ssl->ssl_pm;

    mbedtls_ctr_drbg_free(&ssl_pm->ctr_drbg);
    mbedtls_entropy_free(&ssl_pm->entropy);
    mbedtls_ssl_config_free(&ssl_pm->conf);
    mbedtls_ssl_free(&ssl_pm->ssl);

    ssl_mem_free(ssl_pm);
    ssl->ssl_pm = NULL;
}