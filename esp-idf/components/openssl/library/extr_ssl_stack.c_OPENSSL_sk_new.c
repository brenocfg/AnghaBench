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
struct TYPE_4__ {char** data; int num_alloc; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  OPENSSL_sk_compfunc ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int MIN_NODES ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_STACK_ERROR_LEVEL ; 
 int /*<<< orphan*/  ssl_mem_free (TYPE_1__*) ; 
 void* ssl_mem_zalloc (int) ; 

OPENSSL_STACK* OPENSSL_sk_new(OPENSSL_sk_compfunc c)
{
    OPENSSL_STACK *stack;
    char **data;

    stack = ssl_mem_zalloc(sizeof(OPENSSL_STACK));
    if (!stack) {
        SSL_DEBUG(SSL_STACK_ERROR_LEVEL, "no enough memory > (stack)");
        goto no_mem1;
    }

    data = ssl_mem_zalloc(sizeof(*data) * MIN_NODES);
    if (!data) {
        SSL_DEBUG(SSL_STACK_ERROR_LEVEL, "no enough memory > (data)");
        goto no_mem2;
    }

    stack->data = data;
    stack->num_alloc = MIN_NODES;
    stack->c = c;

    return stack;

no_mem2:
    ssl_mem_free(stack);
no_mem1:
    return NULL;
}