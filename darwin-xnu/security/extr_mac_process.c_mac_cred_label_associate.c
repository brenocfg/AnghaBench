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
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  cred_label_associate ; 

void
mac_cred_label_associate(struct ucred *parent_cred, struct ucred *child_cred)
{

	MAC_PERFORM(cred_label_associate, parent_cred, child_cred);
}