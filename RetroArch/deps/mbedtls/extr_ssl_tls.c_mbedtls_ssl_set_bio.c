#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_ssl_send_t ;
typedef  int /*<<< orphan*/  mbedtls_ssl_recv_timeout_t ;
typedef  int /*<<< orphan*/  mbedtls_ssl_recv_t ;
struct TYPE_3__ {int /*<<< orphan*/ * f_recv_timeout; int /*<<< orphan*/ * f_recv; int /*<<< orphan*/ * f_send; void* p_bio; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */

void mbedtls_ssl_set_bio( mbedtls_ssl_context *ssl,
        void *p_bio,
        mbedtls_ssl_send_t *f_send,
        mbedtls_ssl_recv_t *f_recv,
        mbedtls_ssl_recv_timeout_t *f_recv_timeout )
{
    ssl->p_bio          = p_bio;
    ssl->f_send         = f_send;
    ssl->f_recv         = f_recv;
    ssl->f_recv_timeout = f_recv_timeout;
}