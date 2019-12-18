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
 int /*<<< orphan*/  SSL_ASSERT1 (int) ; 
 int /*<<< orphan*/  SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fd ; 

int SSL_set_fd(SSL *ssl, int fd)
{
    SSL_ASSERT1(ssl);
    SSL_ASSERT1(fd >= 0);

    SSL_METHOD_CALL(set_fd, ssl, fd, 0);

    return 1;
}