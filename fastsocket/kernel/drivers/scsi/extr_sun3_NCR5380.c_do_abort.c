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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 unsigned char ABORT ; 
 int ICR_ASSERT_ACK ; 
 int ICR_ASSERT_ATN ; 
 int ICR_BASE ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 unsigned char NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR5380_transfer_pio (struct Scsi_Host*,unsigned char*,int*,unsigned char**) ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int) ; 
 unsigned char PHASE_MASK ; 
 unsigned char PHASE_MSGOUT ; 
 int PHASE_SR_TO_TCR (unsigned char) ; 
 unsigned char SR_REQ ; 
 int /*<<< orphan*/  STATUS_REG ; 
 int /*<<< orphan*/  TARGET_COMMAND_REG ; 

__attribute__((used)) static int do_abort (struct Scsi_Host *host) 
{
    unsigned char tmp, *msgptr, phase;
    int len;

    /* Request message out phase */
    NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);

    /* 
     * Wait for the target to indicate a valid phase by asserting 
     * REQ.  Once this happens, we'll have either a MSGOUT phase 
     * and can immediately send the ABORT message, or we'll have some 
     * other phase and will have to source/sink data.
     * 
     * We really don't care what value was on the bus or what value
     * the target sees, so we just handshake.
     */
    
    while (!((tmp = NCR5380_read(STATUS_REG)) & SR_REQ));

    NCR5380_write(TARGET_COMMAND_REG, PHASE_SR_TO_TCR(tmp));

    if ((tmp & PHASE_MASK) != PHASE_MSGOUT) {
	NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN | 
		      ICR_ASSERT_ACK);
	while (NCR5380_read(STATUS_REG) & SR_REQ);
	NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
    }
   
    tmp = ABORT;
    msgptr = &tmp;
    len = 1;
    phase = PHASE_MSGOUT;
    NCR5380_transfer_pio (host, &phase, &len, &msgptr);

    /*
     * If we got here, and the command completed successfully,
     * we're about to go into bus free state.
     */

    return len ? -1 : 0;
}