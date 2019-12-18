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
struct nfs4_stateid {int /*<<< orphan*/  st_perstateowner; int /*<<< orphan*/  st_perfile; int /*<<< orphan*/  st_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unhash_generic_stateid(struct nfs4_stateid *stp)
{
	list_del(&stp->st_hash);
	list_del(&stp->st_perfile);
	list_del(&stp->st_perstateowner);
}