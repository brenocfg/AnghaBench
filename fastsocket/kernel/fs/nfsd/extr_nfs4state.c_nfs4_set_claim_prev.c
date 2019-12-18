#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_open {TYPE_2__* op_stateowner; } ;
struct TYPE_4__ {int so_confirmed; TYPE_1__* so_client; } ;
struct TYPE_3__ {int cl_firststate; } ;

/* Variables and functions */

__attribute__((used)) static void
nfs4_set_claim_prev(struct nfsd4_open *open)
{
	open->op_stateowner->so_confirmed = 1;
	open->op_stateowner->so_client->cl_firststate = 1;
}