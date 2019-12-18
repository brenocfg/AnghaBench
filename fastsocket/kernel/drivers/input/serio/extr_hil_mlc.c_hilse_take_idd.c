#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* idd; } ;
struct TYPE_5__ {int* ipacket; int /*<<< orphan*/  ddi; TYPE_1__ di_scratch; } ;
typedef  TYPE_2__ hil_mlc ;

/* Variables and functions */
 int HILSEN_DOWN ; 
 int HILSEN_NEXT ; 
 int HIL_CMD_IDD ; 
 int HIL_IDD_HEADER_EXD ; 
 int HIL_IDD_HEADER_RSC ; 
 int HIL_PKT_ADDR_MASK ; 
 int HIL_PKT_CMD ; 
 int HIL_PKT_DATA_MASK ; 

__attribute__((used)) static int hilse_take_idd(hil_mlc *mlc, int unused)
{
	int i;

	/* Help the state engine:
	 * Is this a real IDD response or just an echo?
	 *
	 * Real IDD response does not start with a command.
	 */
	if (mlc->ipacket[0] & HIL_PKT_CMD)
		goto bail;

	/* Should have the command echoed further down. */
	for (i = 1; i < 16; i++) {
		if (((mlc->ipacket[i] & HIL_PKT_ADDR_MASK) ==
		     (mlc->ipacket[0] & HIL_PKT_ADDR_MASK)) &&
		    (mlc->ipacket[i] & HIL_PKT_CMD) &&
		    ((mlc->ipacket[i] & HIL_PKT_DATA_MASK) == HIL_CMD_IDD))
			break;
	}
	if (i > 15)
		goto bail;

	/* And the rest of the packets should still be clear. */
	while (++i < 16)
		if (mlc->ipacket[i])
			break;

	if (i < 16)
		goto bail;

	for (i = 0; i < 16; i++)
		mlc->di_scratch.idd[i] =
			mlc->ipacket[i] & HIL_PKT_DATA_MASK;

	/* Next step is to see if RSC supported */
	if (mlc->di_scratch.idd[1] & HIL_IDD_HEADER_RSC)
		return HILSEN_NEXT;

	if (mlc->di_scratch.idd[1] & HIL_IDD_HEADER_EXD)
		return HILSEN_DOWN | 4;

	return 0;

 bail:
	mlc->ddi--;

	return -1; /* This should send us off to ACF */
}