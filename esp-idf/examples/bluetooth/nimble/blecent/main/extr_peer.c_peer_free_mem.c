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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * peer_chr_mem ; 
 int /*<<< orphan*/ * peer_dsc_mem ; 
 int /*<<< orphan*/ * peer_mem ; 
 int /*<<< orphan*/ * peer_svc_mem ; 

__attribute__((used)) static void
peer_free_mem(void)
{
    free(peer_mem);
    peer_mem = NULL;

    free(peer_svc_mem);
    peer_svc_mem = NULL;

    free(peer_chr_mem);
    peer_chr_mem = NULL;

    free(peer_dsc_mem);
    peer_dsc_mem = NULL;
}