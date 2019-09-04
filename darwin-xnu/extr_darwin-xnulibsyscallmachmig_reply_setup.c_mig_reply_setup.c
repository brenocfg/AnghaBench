#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int msgh_size; scalar_t__ msgh_id; int /*<<< orphan*/  msgh_local_port; int /*<<< orphan*/  msgh_remote_port; int /*<<< orphan*/  msgh_bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  NDR; TYPE_1__ Head; } ;
typedef  TYPE_2__ mig_reply_error_t ;
struct TYPE_8__ {scalar_t__ msgh_id; int /*<<< orphan*/  msgh_local_port; int /*<<< orphan*/  msgh_bits; } ;
typedef  TYPE_3__ mach_msg_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  NDR_record ; 

void
mig_reply_setup(mach_msg_header_t *request, mach_msg_header_t *reply)
{
#define	InP	(request)
#define	OutP	((mig_reply_error_t *) reply)

	OutP->Head.msgh_bits =
		MACH_MSGH_BITS(MACH_MSGH_BITS_LOCAL(InP->msgh_bits), 0);
	OutP->Head.msgh_size = sizeof(mig_reply_error_t);
	OutP->Head.msgh_remote_port = InP->msgh_local_port;
	OutP->Head.msgh_local_port  = MACH_PORT_NULL;
	OutP->Head.msgh_id = InP->msgh_id + 100;
	OutP->NDR = NDR_record;
}