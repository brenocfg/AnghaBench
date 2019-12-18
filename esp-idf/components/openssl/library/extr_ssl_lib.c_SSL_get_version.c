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
 int /*<<< orphan*/  SSL_ASSERT2 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_version (int /*<<< orphan*/  const*) ; 
 char const* ssl_protocol_to_string (int /*<<< orphan*/ ) ; 

const char *SSL_get_version(const SSL *ssl)
{
    SSL_ASSERT2(ssl);

    return ssl_protocol_to_string(SSL_version(ssl));
}