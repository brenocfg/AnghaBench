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
struct pkey_pm {int /*<<< orphan*/  pkey; int /*<<< orphan*/  ex_pkey; } ;
struct TYPE_4__ {struct pkey_pm* pkey_pm; } ;
typedef  TYPE_1__ EVP_PKEY ;

/* Variables and functions */
 struct pkey_pm* ssl_mem_zalloc (int) ; 

int pkey_pm_new(EVP_PKEY *pk, EVP_PKEY *m_pkey)
{
    struct pkey_pm *pkey_pm;

    pkey_pm = ssl_mem_zalloc(sizeof(struct pkey_pm));
    if (!pkey_pm)
        return -1;

    pk->pkey_pm = pkey_pm;

    if (m_pkey) {
        struct pkey_pm *m_pkey_pm = (struct pkey_pm *)m_pkey->pkey_pm;

        pkey_pm->ex_pkey = m_pkey_pm->pkey;
    }

    return 0;
}