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
struct irlap_cb {int vr; } ;

/* Variables and functions */
 int NS_EXPECTED ; 
 int NS_UNEXPECTED ; 

int irlap_validate_ns_received(struct irlap_cb *self, int ns)
{
	/*  ns as expected?  */
	if (ns == self->vr)
		return NS_EXPECTED;
	/*
	 *  Stations are allowed to treat invalid NS as unexpected NS
	 *  IrLAP, Recv ... with-invalid-Ns. p. 84
	 */
	return NS_UNEXPECTED;

	/* return NR_INVALID; */
}