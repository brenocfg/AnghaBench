#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* cert; } ;
struct TYPE_5__ {int /*<<< orphan*/ * x509; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT2 (TYPE_2__ const*) ; 

X509 *SSL_get_certificate(const SSL *ssl)
{
    SSL_ASSERT2(ssl);

    return ssl->cert->x509;
}