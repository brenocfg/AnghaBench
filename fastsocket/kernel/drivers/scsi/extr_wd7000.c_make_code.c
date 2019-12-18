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
 unsigned int DID_ABORT ; 
 unsigned int DID_BAD_INTR ; 
 unsigned int DID_BAD_TARGET ; 
 unsigned int DID_ERROR ; 
 unsigned int DID_OK ; 
 unsigned int DID_RESET ; 
 unsigned int DID_TIME_OUT ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int make_code(unsigned hosterr, unsigned scsierr)
{
#ifdef WD7000_DEBUG
	int in_error = hosterr;
#endif

	switch ((hosterr >> 8) & 0xff) {
	case 0:		/* Reserved */
		hosterr = DID_ERROR;
		break;
	case 1:		/* Command Complete, no errors */
		hosterr = DID_OK;
		break;
	case 2:		/* Command complete, error logged in scb status (scsierr) */
		hosterr = DID_OK;
		break;
	case 4:		/* Command failed to complete - timeout */
		hosterr = DID_TIME_OUT;
		break;
	case 5:		/* Command terminated; Bus reset by external device */
		hosterr = DID_RESET;
		break;
	case 6:		/* Unexpected Command Received w/ host as target */
		hosterr = DID_BAD_TARGET;
		break;
	case 80:		/* Unexpected Reselection */
	case 81:		/* Unexpected Selection */
		hosterr = DID_BAD_INTR;
		break;
	case 82:		/* Abort Command Message  */
		hosterr = DID_ABORT;
		break;
	case 83:		/* SCSI Bus Software Reset */
	case 84:		/* SCSI Bus Hardware Reset */
		hosterr = DID_RESET;
		break;
	default:		/* Reserved */
		hosterr = DID_ERROR;
	}
#ifdef WD7000_DEBUG
	if (scsierr || hosterr)
		dprintk("\nSCSI command error: SCSI 0x%02x host 0x%04x return %d\n", scsierr, in_error, hosterr);
#endif
	return (scsierr | (hosterr << 16));
}