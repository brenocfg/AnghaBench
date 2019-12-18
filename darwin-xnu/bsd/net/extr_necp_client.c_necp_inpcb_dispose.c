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
struct TYPE_2__ {int /*<<< orphan*/ * inp_account; int /*<<< orphan*/ * inp_domain; } ;
struct inpcb {TYPE_1__ inp_necp_attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int /*<<< orphan*/  necp_inpcb_remove_cb (struct inpcb*) ; 

void
necp_inpcb_dispose(struct inpcb *inp)
{
	necp_inpcb_remove_cb(inp); // Clear out socket registrations if not yet done
	if (inp->inp_necp_attributes.inp_domain != NULL) {
		FREE(inp->inp_necp_attributes.inp_domain, M_NECP);
		inp->inp_necp_attributes.inp_domain = NULL;
	}
	if (inp->inp_necp_attributes.inp_account != NULL) {
		FREE(inp->inp_necp_attributes.inp_account, M_NECP);
		inp->inp_necp_attributes.inp_account = NULL;
	}
}