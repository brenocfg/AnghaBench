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
 int /*<<< orphan*/  SSL_ASSERT3 (size_t) ; 
 int /*<<< orphan*/  SSL_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  set_bufflen ; 

void SSL_set_default_read_buffer_len(SSL *ssl, size_t len)
{
    SSL_ASSERT3(ssl);
    SSL_ASSERT3(len);

    SSL_METHOD_CALL(set_bufflen, ssl, len);
}