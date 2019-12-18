#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_tls_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  _esp_create_ssl_handle (char const*,size_t,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t create_ssl_handle(const char *hostname, size_t hostlen, const void *cfg, esp_tls_t *tls)
{
    return _esp_create_ssl_handle(hostname, hostlen, cfg, tls);
}