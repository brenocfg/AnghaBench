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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 long H_VASI_ENABLED ; 
 int /*<<< orphan*/  H_VASI_STATE ; 
 long H_VASI_SUSPENDING ; 
 int PLPAR_HCALL_BUFSIZE ; 
 long plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  stream_id ; 

__attribute__((used)) static int pseries_suspend_begin(suspend_state_t state)
{
	long vasi_state, rc;
	unsigned long retbuf[PLPAR_HCALL_BUFSIZE];

	/* Make sure the state is valid */
	rc = plpar_hcall(H_VASI_STATE, retbuf, stream_id);

	vasi_state = retbuf[0];

	if (rc) {
		pr_err("pseries_suspend_begin: vasi_state returned %ld\n",rc);
		return rc;
	} else if (vasi_state == H_VASI_ENABLED) {
		return -EAGAIN;
	} else if (vasi_state != H_VASI_SUSPENDING) {
		pr_err("pseries_suspend_begin: vasi_state returned state %ld\n",
		       vasi_state);
		return -EIO;
	}

	return 0;
}