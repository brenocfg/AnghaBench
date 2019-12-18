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
struct peer_svc {int dummy; } ;
struct peer_dsc {int dummy; } ;
struct peer_chr {int dummy; } ;
struct peer {int dummy; } ;

/* Variables and functions */
 int BLE_HS_ENOMEM ; 
 int BLE_HS_EOS ; 
 int /*<<< orphan*/  OS_MEMPOOL_BYTES (int,int) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int os_mempool_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * peer_chr_mem ; 
 int /*<<< orphan*/  peer_chr_pool ; 
 int /*<<< orphan*/ * peer_dsc_mem ; 
 int /*<<< orphan*/  peer_dsc_pool ; 
 int /*<<< orphan*/  peer_free_mem () ; 
 int /*<<< orphan*/ * peer_mem ; 
 int /*<<< orphan*/  peer_pool ; 
 int /*<<< orphan*/ * peer_svc_mem ; 
 int /*<<< orphan*/  peer_svc_pool ; 

int
peer_init(int max_peers, int max_svcs, int max_chrs, int max_dscs)
{
    int rc;

    /* Free memory first in case this function gets called more than once. */
    peer_free_mem();

    peer_mem = malloc(
                   OS_MEMPOOL_BYTES(max_peers, sizeof (struct peer)));
    if (peer_mem == NULL) {
        rc = BLE_HS_ENOMEM;
        goto err;
    }

    rc = os_mempool_init(&peer_pool, max_peers,
                         sizeof (struct peer), peer_mem,
                         "peer_pool");
    if (rc != 0) {
        rc = BLE_HS_EOS;
        goto err;
    }

    peer_svc_mem = malloc(
                       OS_MEMPOOL_BYTES(max_svcs, sizeof (struct peer_svc)));
    if (peer_svc_mem == NULL) {
        rc = BLE_HS_ENOMEM;
        goto err;
    }

    rc = os_mempool_init(&peer_svc_pool, max_svcs,
                         sizeof (struct peer_svc), peer_svc_mem,
                         "peer_svc_pool");
    if (rc != 0) {
        rc = BLE_HS_EOS;
        goto err;
    }

    peer_chr_mem = malloc(
                       OS_MEMPOOL_BYTES(max_chrs, sizeof (struct peer_chr)));
    if (peer_chr_mem == NULL) {
        rc = BLE_HS_ENOMEM;
        goto err;
    }

    rc = os_mempool_init(&peer_chr_pool, max_chrs,
                         sizeof (struct peer_chr), peer_chr_mem,
                         "peer_chr_pool");
    if (rc != 0) {
        rc = BLE_HS_EOS;
        goto err;
    }

    peer_dsc_mem = malloc(
                       OS_MEMPOOL_BYTES(max_dscs, sizeof (struct peer_dsc)));
    if (peer_dsc_mem == NULL) {
        rc = BLE_HS_ENOMEM;
        goto err;
    }

    rc = os_mempool_init(&peer_dsc_pool, max_dscs,
                         sizeof (struct peer_dsc), peer_dsc_mem,
                         "peer_dsc_pool");
    if (rc != 0) {
        rc = BLE_HS_EOS;
        goto err;
    }

    return 0;

err:
    peer_free_mem();
    return rc;
}