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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_METHOD_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ASSERT3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  ssl_mem_free (int /*<<< orphan*/ *) ; 

void EVP_PKEY_free(EVP_PKEY *pkey)
{
    SSL_ASSERT3(pkey);

    EVP_PKEY_METHOD_CALL(free, pkey);

    ssl_mem_free(pkey);
}