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
 int SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_ST_OK ; 
 int /*<<< orphan*/  shutdown ; 

int SSL_shutdown(SSL *ssl)
{
    int ret;

    SSL_ASSERT1(ssl);

    if (SSL_get_state(ssl) != TLS_ST_OK) return 1;

    ret = SSL_METHOD_CALL(shutdown, ssl);

    return ret;
}