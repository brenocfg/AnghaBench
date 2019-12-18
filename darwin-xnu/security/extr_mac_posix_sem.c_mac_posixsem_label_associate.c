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
struct pseminfo {int /*<<< orphan*/  psem_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pseminfo*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  posixsem_label_associate ; 

void
mac_posixsem_label_associate(kauth_cred_t cred, struct pseminfo *psem,
    const char *name)
{

	MAC_PERFORM(posixsem_label_associate, cred, psem, psem->psem_label, name);
}