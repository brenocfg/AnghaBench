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

/* Variables and functions */
 scalar_t__ GSS_KRB5_INITIALIZED ; 
 int /*<<< orphan*/  GSS_KRB5_INITIALIZING ; 
 int /*<<< orphan*/  GSS_KRB5_NOT_INITIALIZED ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  OSCompareAndSwap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gss_krb5_mech_grp ; 
 scalar_t__ gss_krb5_mech_initted ; 
 int /*<<< orphan*/  gss_krb5_mech_is_initialized () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 

void
gss_krb5_mech_init(void)
{
	extern void IOSleep(int);

	/* Once initted always initted */
	if (gss_krb5_mech_initted == GSS_KRB5_INITIALIZED)
		return;

	/* make sure we init only once */
	if (!OSCompareAndSwap(GSS_KRB5_NOT_INITIALIZED, GSS_KRB5_INITIALIZING, &gss_krb5_mech_initted)) {
		/* wait until initialization is complete */
		while (!gss_krb5_mech_is_initialized())
			IOSleep(10);
		return;
	}
	gss_krb5_mech_grp = lck_grp_alloc_init("gss_krb5_mech", LCK_GRP_ATTR_NULL);
	gss_krb5_mech_initted = GSS_KRB5_INITIALIZED;
}