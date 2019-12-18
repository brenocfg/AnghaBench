#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ref_counter; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT3 (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_METHOD_CALL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 

void X509_free(X509 *x)
{
    SSL_ASSERT3(x);

    if (--x->ref_counter > 0) {
        return;
    }

    X509_METHOD_CALL(free, x);

    ssl_mem_free(x);
}