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
typedef  scalar_t__ uint32_t ;
struct ssl_pm {int /*<<< orphan*/  ssl; } ;
struct TYPE_3__ {scalar_t__ ssl_pm; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 long X509_V_ERR_UNSPECIFIED ; 
 long X509_V_OK ; 
 scalar_t__ mbedtls_ssl_get_verify_result (int /*<<< orphan*/ *) ; 

long ssl_pm_get_verify_result(const SSL *ssl)
{
    uint32_t ret;
    long verify_result;
    struct ssl_pm *ssl_pm = (struct ssl_pm *)ssl->ssl_pm;

    ret = mbedtls_ssl_get_verify_result(&ssl_pm->ssl);
    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ssl_get_verify_result() return 0x%x", ret);
        verify_result = X509_V_ERR_UNSPECIFIED;
    } else
        verify_result = X509_V_OK;

    return verify_result;
}