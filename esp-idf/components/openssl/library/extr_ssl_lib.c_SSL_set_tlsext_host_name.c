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
typedef  char const SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (char const*) ; 
 int /*<<< orphan*/  SSL_METHOD_CALL (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  set_hostname ; 

int SSL_set_tlsext_host_name(SSL* ssl, const char *hostname)
{
     SSL_ASSERT1(ssl);
     SSL_ASSERT1(hostname);

     SSL_METHOD_CALL(set_hostname, ssl, hostname);

     return 1;
}