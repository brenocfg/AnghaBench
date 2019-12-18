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
struct pkey_pm {int /*<<< orphan*/ * pkey; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pkey_pm; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (int /*<<< orphan*/ *) ; 

void pkey_pm_free(EVP_PKEY *pk)
{
    struct pkey_pm *pkey_pm = (struct pkey_pm *)pk->pkey_pm;

    if (pkey_pm->pkey) {
        mbedtls_pk_free(pkey_pm->pkey);

        ssl_mem_free(pkey_pm->pkey);
        pkey_pm->pkey = NULL;
    }

    ssl_mem_free(pk->pkey_pm);
    pk->pkey_pm = NULL;
}