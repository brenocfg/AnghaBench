#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT2 (TYPE_1__ const*) ; 

SSL_CTX *SSL_get_SSL_CTX(const SSL *ssl)
{
    SSL_ASSERT2(ssl);

    return ssl->ctx;
}