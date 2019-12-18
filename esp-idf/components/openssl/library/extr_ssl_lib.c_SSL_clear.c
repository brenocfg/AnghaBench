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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SSL_LIB_ERROR_LEVEL ; 
 int SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  new ; 

int SSL_clear(SSL *ssl)
{
    int ret;

    SSL_ASSERT1(ssl);

    ret = SSL_shutdown(ssl);
    if (1 != ret) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "SSL_shutdown return %d", ret);
        goto failed1;
    }

    SSL_METHOD_CALL(free, ssl);

    ret = SSL_METHOD_CALL(new, ssl);
    if (!ret) {
        SSL_DEBUG(SSL_LIB_ERROR_LEVEL, "SSL_METHOD_CALL(new) return %d", ret);
        goto failed1;
    }

    return 1;

failed1:
    return ret;
}