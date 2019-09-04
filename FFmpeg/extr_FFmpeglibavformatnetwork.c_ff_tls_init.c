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

/* Variables and functions */

int ff_tls_init(void)
{
#if CONFIG_TLS_PROTOCOL
#if CONFIG_OPENSSL
    int ret;
    if ((ret = ff_openssl_init()) < 0)
        return ret;
#endif
#if CONFIG_GNUTLS
    ff_gnutls_init();
#endif
#endif
    return 0;
}