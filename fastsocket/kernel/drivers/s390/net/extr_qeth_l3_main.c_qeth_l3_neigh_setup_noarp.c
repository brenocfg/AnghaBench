#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct neighbour {TYPE_1__* ops; int /*<<< orphan*/  output; int /*<<< orphan*/  ha; int /*<<< orphan*/  nud_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  connected_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUD_NOARP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int qeth_l3_neigh_setup_noarp(struct neighbour *n)
{
	n->nud_state = NUD_NOARP;
	memcpy(n->ha, "FAKELL", 6);
	n->output = n->ops->connected_output;
	return 0;
}