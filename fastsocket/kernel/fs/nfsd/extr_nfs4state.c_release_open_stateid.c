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
struct nfs4_stateid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_generic_stateid (struct nfs4_stateid*) ; 
 int /*<<< orphan*/  release_stateid_lockowners (struct nfs4_stateid*) ; 
 int /*<<< orphan*/  unhash_generic_stateid (struct nfs4_stateid*) ; 

__attribute__((used)) static void release_open_stateid(struct nfs4_stateid *stp)
{
	unhash_generic_stateid(stp);
	release_stateid_lockowners(stp);
	free_generic_stateid(stp);
}