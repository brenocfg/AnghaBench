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
struct nfs4_stateowner {int /*<<< orphan*/  so_close_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_put_stateowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  unhash_openowner (struct nfs4_stateowner*) ; 

__attribute__((used)) static void release_openowner(struct nfs4_stateowner *sop)
{
	unhash_openowner(sop);
	list_del(&sop->so_close_lru);
	nfs4_put_stateowner(sop);
}