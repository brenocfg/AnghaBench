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
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
#define  ECN_COMPATIBILITY 130 
#define  ECN_NOCARE 129 
#define  ECN_NORMAL 128 
 int /*<<< orphan*/  IPTOS_ECN_MASK ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ip_ecn_ingress(int mode, u_int8_t *outer, const u_int8_t *inner)
{
	if (!outer || !inner)
		panic("NULL pointer passed to ip_ecn_ingress");

	*outer = *inner;
	switch (mode) {
	case ECN_NORMAL:		/* ECN normal mode, copy flags */
		break;
	case ECN_COMPATIBILITY:		/* ECN compatibility mode */
		*outer &= ~IPTOS_ECN_MASK;
		break;
	case ECN_NOCARE:	/* no consideration to ECN */
		break;
	}
}