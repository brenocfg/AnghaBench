#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_ASSERT3 (TYPE_1__*) ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 

void OPENSSL_sk_free(OPENSSL_STACK *stack)
{
    SSL_ASSERT3(stack);

    ssl_mem_free(stack->data);
    ssl_mem_free(stack);
}