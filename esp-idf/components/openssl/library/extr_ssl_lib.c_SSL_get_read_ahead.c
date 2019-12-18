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
struct TYPE_5__ {int read_ahead; } ;
struct TYPE_6__ {TYPE_1__ rlayer; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT1 (TYPE_2__ const*) ; 

int SSL_get_read_ahead(const SSL *ssl)
{
    SSL_ASSERT1(ssl);

    return ssl->rlayer.read_ahead;
}