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
struct ksign_signature {int sig_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  _debug (char*,int) ; 

__attribute__((used)) static int ksign_grab_signature(struct ksign_signature *sig, void *fnxdata)
{
	struct ksign_signature **_sig = fnxdata;

	if (sig->sig_class != 0x00) {
		_debug("ksign: standalone signature of class 0x%02x\n",
		       sig->sig_class);
		return 1;
	}

	if (*_sig)
		return 1;

	*_sig = sig;
	return 0;
}