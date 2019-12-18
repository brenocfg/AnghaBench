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
 scalar_t__ SSL_WRITING ; 
 scalar_t__ SSL_want (int /*<<< orphan*/  const*) ; 

int SSL_want_x509_lookup(const SSL *ssl)
{
    SSL_ASSERT1(ssl);

    return (SSL_want(ssl) == SSL_WRITING);
}