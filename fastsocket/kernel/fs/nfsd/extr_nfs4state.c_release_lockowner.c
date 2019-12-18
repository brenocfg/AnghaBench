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
struct nfs4_stateowner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_put_stateowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  unhash_lockowner (struct nfs4_stateowner*) ; 

__attribute__((used)) static void release_lockowner(struct nfs4_stateowner *sop)
{
	unhash_lockowner(sop);
	nfs4_put_stateowner(sop);
}