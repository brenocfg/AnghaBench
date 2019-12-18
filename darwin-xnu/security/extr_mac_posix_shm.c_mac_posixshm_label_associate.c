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
struct pshminfo {int /*<<< orphan*/  pshm_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pshminfo*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  posixshm_label_associate ; 

void
mac_posixshm_label_associate(kauth_cred_t cred, struct pshminfo *pshm,
    const char *name)
{

	MAC_PERFORM(posixshm_label_associate, cred, pshm, pshm->pshm_label, name);
}