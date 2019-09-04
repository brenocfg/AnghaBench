#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct label {int dummy; } ;
typedef  TYPE_1__* posix_cred_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_3__ {int /*<<< orphan*/  cr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRF_MAC_ENFORCE ; 
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  cred_label_update ; 
 TYPE_1__* posix_cred_get (int /*<<< orphan*/ ) ; 

void
mac_cred_label_update(kauth_cred_t cred, struct label *newlabel)
{
	posix_cred_t pcred = posix_cred_get(cred);

	/* force label to be part of "matching" for credential */
	pcred->cr_flags |= CRF_MAC_ENFORCE;

	/* inform the policies of the update */
	MAC_PERFORM(cred_label_update, cred, newlabel);
}