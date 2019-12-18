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
 int /*<<< orphan*/  SSL_ASSERT1 (int /*<<< orphan*/  const*) ; 
 int SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fd ; 

int SSL_get_rfd(const SSL *ssl)
{
    int ret;

    SSL_ASSERT1(ssl);

    ret = SSL_METHOD_CALL(get_fd, ssl, 0);

    return ret;
}