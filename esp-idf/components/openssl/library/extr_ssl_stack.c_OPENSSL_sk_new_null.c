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
typedef  int /*<<< orphan*/  OPENSSL_sk_compfunc ;
typedef  int /*<<< orphan*/  OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_sk_new (int /*<<< orphan*/ ) ; 

OPENSSL_STACK *OPENSSL_sk_new_null(void)
{
    return OPENSSL_sk_new((OPENSSL_sk_compfunc)NULL);
}