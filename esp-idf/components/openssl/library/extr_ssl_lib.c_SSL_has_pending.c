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
 scalar_t__ SSL_pending (int /*<<< orphan*/  const*) ; 

int SSL_has_pending(const SSL *ssl)
{
    int ret;

    SSL_ASSERT1(ssl);

    if (SSL_pending(ssl))
        ret = 1;
    else
        ret = 0;

    return ret;
}