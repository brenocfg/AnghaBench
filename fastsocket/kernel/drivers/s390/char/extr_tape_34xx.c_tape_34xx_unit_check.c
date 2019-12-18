#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tape_request {int op; int /*<<< orphan*/  retries; } ;
struct TYPE_6__ {int block_position; } ;
struct tape_device {int* modeset_byte; TYPE_2__* cdev; TYPE_3__ blk_data; } ;
struct irb {int* ecw; } ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  driver_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EMEDIUMTYPE ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  MS_UNLOADED ; 
 int SENSE_BEGINNING_OF_TAPE ; 
 int SENSE_BUS_OUT_CHECK ; 
 int SENSE_COMMAND_REJECT ; 
 int SENSE_DATA_CHECK ; 
 int SENSE_DEFERRED_UNIT_CHECK ; 
 int SENSE_DRIVE_ONLINE ; 
 int SENSE_EQUIPMENT_CHECK ; 
 int SENSE_OVERRUN ; 
 int SENSE_RECORD_SEQUENCE_ERR ; 
 int SENSE_TAPE_SYNC_MODE ; 
 int SENSE_WRITE_MODE ; 
 int SENSE_WRITE_PROTECT ; 
 int TAPE_IO_SUCCESS ; 
#define  TO_ASSIGN 137 
 int TO_BLOCK ; 
#define  TO_BSB 136 
#define  TO_DIS 135 
 int TO_DSE ; 
#define  TO_FSB 134 
#define  TO_FSF 133 
#define  TO_LBL 132 
#define  TO_NOP 131 
#define  TO_RFO 130 
 int TO_RUN ; 
#define  TO_UNASSIGN 129 
#define  TO_WRI 128 
 int TO_WTM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tape_3480 ; 
 int /*<<< orphan*/  tape_3490 ; 
 int /*<<< orphan*/  tape_34xx_delete_sbid_from (struct tape_device*,int /*<<< orphan*/ ) ; 
 int tape_34xx_done (struct tape_request*) ; 
 int tape_34xx_erp_bug (struct tape_device*,struct tape_request*,struct irb*,int) ; 
 int tape_34xx_erp_failed (struct tape_request*,int /*<<< orphan*/ ) ; 
 int tape_34xx_erp_overrun (struct tape_device*,struct tape_request*,struct irb*) ; 
 int tape_34xx_erp_read_opposite (struct tape_device*,struct tape_request*) ; 
 int tape_34xx_erp_retry (struct tape_request*) ; 
 int tape_34xx_erp_sequence (struct tape_device*,struct tape_request*,struct irb*) ; 
 int tape_34xx_erp_succeeded (struct tape_request*) ; 
 int /*<<< orphan*/  tape_med_state_set (struct tape_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tape_34xx_unit_check(struct tape_device *device, struct tape_request *request,
		     struct irb *irb)
{
	int inhibit_cu_recovery;
	__u8* sense;

	inhibit_cu_recovery = (*device->modeset_byte & 0x80) ? 1 : 0;
	sense = irb->ecw;

#ifdef CONFIG_S390_TAPE_BLOCK
	if (request->op == TO_BLOCK) {
		/*
		 * Recovery for block device requests. Set the block_position
		 * to something invalid and retry.
		 */
		device->blk_data.block_position = -1;
		if (request->retries-- <= 0)
			return tape_34xx_erp_failed(request, -EIO);
		else
			return tape_34xx_erp_retry(request);
	}
#endif

	if (
		sense[0] & SENSE_COMMAND_REJECT &&
		sense[1] & SENSE_WRITE_PROTECT
	) {
		if (
			request->op == TO_DSE ||
			request->op == TO_WRI ||
			request->op == TO_WTM
		) {
			/* medium is write protected */
			return tape_34xx_erp_failed(request, -EACCES);
		} else {
			return tape_34xx_erp_bug(device, request, irb, -3);
		}
	}

	/*
	 * Special cases for various tape-states when reaching
	 * end of recorded area
	 *
	 * FIXME: Maybe a special case of the special case:
	 *        sense[0] == SENSE_EQUIPMENT_CHECK &&
	 *        sense[1] == SENSE_DRIVE_ONLINE    &&
	 *        sense[3] == 0x47 (Volume Fenced)
	 *
	 *        This was caused by continued FSF or FSR after an
	 *        'End Of Data'.
	 */
	if ((
		sense[0] == SENSE_DATA_CHECK      ||
		sense[0] == SENSE_EQUIPMENT_CHECK ||
		sense[0] == SENSE_EQUIPMENT_CHECK + SENSE_DEFERRED_UNIT_CHECK
	) && (
		sense[1] == SENSE_DRIVE_ONLINE ||
		sense[1] == SENSE_BEGINNING_OF_TAPE + SENSE_WRITE_MODE
	)) {
		switch (request->op) {
		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DRIVE_ONLINE
		 * sense[3] == 0x36 (End Of Data)
		 *
		 * Further seeks might return a 'Volume Fenced'.
		 */
		case TO_FSF:
		case TO_FSB:
			/* Trying to seek beyond end of recorded area */
			return tape_34xx_erp_failed(request, -ENOSPC);
		case TO_BSB:
			return tape_34xx_erp_retry(request);

		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DRIVE_ONLINE &&
		 * sense[3] == 0x36 (End Of Data)
		 */
		case TO_LBL:
			/* Block could not be located. */
			tape_34xx_delete_sbid_from(device, 0);
			return tape_34xx_erp_failed(request, -EIO);

		case TO_RFO:
			/* Read beyond end of recorded area -> 0 bytes read */
			return tape_34xx_erp_failed(request, 0);

		/*
		 * sense[0] == SENSE_EQUIPMENT_CHECK &&
		 * sense[1] == SENSE_DRIVE_ONLINE    &&
		 * sense[3] == 0x38 (Physical End Of Volume)
		 */
		case TO_WRI:
			/* Writing at physical end of volume */
			return tape_34xx_erp_failed(request, -ENOSPC);
		default:
			return tape_34xx_erp_failed(request, 0);
		}
	}

	/* Sensing special bits */
	if (sense[0] & SENSE_BUS_OUT_CHECK)
		return tape_34xx_erp_retry(request);

	if (sense[0] & SENSE_DATA_CHECK) {
		/*
		 * hardware failure, damaged tape or improper
		 * operating conditions
		 */
		switch (sense[3]) {
		case 0x23:
			/* a read data check occurred */
			if ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_recovery)
				// data check is not permanent, may be
				// recovered. We always use async-mode with
				// cu-recovery, so this should *never* happen.
				return tape_34xx_erp_bug(device, request,
							 irb, -4);

			/* data check is permanent, CU recovery has failed */
			dev_warn (&device->cdev->dev, "A read error occurred "
				"that cannot be recovered\n");
			return tape_34xx_erp_failed(request, -EIO);
		case 0x25:
			// a write data check occurred
			if ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_recovery)
				// data check is not permanent, may be
				// recovered. We always use async-mode with
				// cu-recovery, so this should *never* happen.
				return tape_34xx_erp_bug(device, request,
							 irb, -5);

			// data check is permanent, cu-recovery has failed
			dev_warn (&device->cdev->dev, "A write error on the "
				"tape cannot be recovered\n");
			return tape_34xx_erp_failed(request, -EIO);
		case 0x26:
			/* Data Check (read opposite) occurred. */
			return tape_34xx_erp_read_opposite(device, request);
		case 0x28:
			/* ID-Mark at tape start couldn't be written */
			dev_warn (&device->cdev->dev, "Writing the ID-mark "
				"failed\n");
			return tape_34xx_erp_failed(request, -EIO);
		case 0x31:
			/* Tape void. Tried to read beyond end of device. */
			dev_warn (&device->cdev->dev, "Reading the tape beyond"
				" the end of the recorded area failed\n");
			return tape_34xx_erp_failed(request, -ENOSPC);
		case 0x41:
			/* Record sequence error. */
			dev_warn (&device->cdev->dev, "The tape contains an "
				"incorrect block ID sequence\n");
			return tape_34xx_erp_failed(request, -EIO);
		default:
			/* all data checks for 3480 should result in one of
			 * the above erpa-codes. For 3490, other data-check
			 * conditions do exist. */
			if (device->cdev->id.driver_info == tape_3480)
				return tape_34xx_erp_bug(device, request,
							 irb, -6);
		}
	}

	if (sense[0] & SENSE_OVERRUN)
		return tape_34xx_erp_overrun(device, request, irb);

	if (sense[1] & SENSE_RECORD_SEQUENCE_ERR)
		return tape_34xx_erp_sequence(device, request, irb);

	/* Sensing erpa codes */
	switch (sense[3]) {
	case 0x00:
		/* Unit check with erpa code 0. Report and ignore. */
		return TAPE_IO_SUCCESS;
	case 0x21:
		/*
		 * Data streaming not operational. CU will switch to
		 * interlock mode. Reissue the command.
		 */
		return tape_34xx_erp_retry(request);
	case 0x22:
		/*
		 * Path equipment check. Might be drive adapter error, buffer
		 * error on the lower interface, internal path not usable,
		 * or error during cartridge load.
		 */
		dev_warn (&device->cdev->dev, "A path equipment check occurred"
			" for the tape device\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x24:
		/*
		 * Load display check. Load display was command was issued,
		 * but the drive is displaying a drive check message. Can
		 * be threated as "device end".
		 */
		return tape_34xx_erp_succeeded(request);
	case 0x27:
		/*
		 * Command reject. May indicate illegal channel program or
		 * buffer over/underrun. Since all channel programs are
		 * issued by this driver and ought be correct, we assume a
		 * over/underrun situation and retry the channel program.
		 */
		return tape_34xx_erp_retry(request);
	case 0x29:
		/*
		 * Function incompatible. Either the tape is idrc compressed
		 * but the hardware isn't capable to do idrc, or a perform
		 * subsystem func is issued and the CU is not on-line.
		 */
		return tape_34xx_erp_failed(request, -EIO);
	case 0x2a:
		/*
		 * Unsolicited environmental data. An internal counter
		 * overflows, we can ignore this and reissue the cmd.
		 */
		return tape_34xx_erp_retry(request);
	case 0x2b:
		/*
		 * Environmental data present. Indicates either unload
		 * completed ok or read buffered log command completed ok.
		 */
		if (request->op == TO_RUN) {
			/* Rewind unload completed ok. */
			tape_med_state_set(device, MS_UNLOADED);
			return tape_34xx_erp_succeeded(request);
		}
		/* tape_34xx doesn't use read buffered log commands. */
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x2c:
		/*
		 * Permanent equipment check. CU has tried recovery, but
		 * did not succeed.
		 */
		return tape_34xx_erp_failed(request, -EIO);
	case 0x2d:
		/* Data security erase failure. */
		if (request->op == TO_DSE)
			return tape_34xx_erp_failed(request, -EIO);
		/* Data security erase failure, but no such command issued. */
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x2e:
		/*
		 * Not capable. This indicates either that the drive fails
		 * reading the format id mark or that that format specified
		 * is not supported by the drive.
		 */
		dev_warn (&device->cdev->dev, "The tape unit cannot process "
			"the tape format\n");
		return tape_34xx_erp_failed(request, -EMEDIUMTYPE);
	case 0x30:
		/* The medium is write protected. */
		dev_warn (&device->cdev->dev, "The tape medium is write-"
			"protected\n");
		return tape_34xx_erp_failed(request, -EACCES);
	case 0x32:
		// Tension loss. We cannot recover this, it's an I/O error.
		dev_warn (&device->cdev->dev, "The tape does not have the "
			"required tape tension\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x33:
		/*
		 * Load Failure. The cartridge was not inserted correctly or
		 * the tape is not threaded correctly.
		 */
		dev_warn (&device->cdev->dev, "The tape unit failed to load"
			" the cartridge\n");
		tape_34xx_delete_sbid_from(device, 0);
		return tape_34xx_erp_failed(request, -EIO);
	case 0x34:
		/*
		 * Unload failure. The drive cannot maintain tape tension
		 * and control tape movement during an unload operation.
		 */
		dev_warn (&device->cdev->dev, "Automatic unloading of the tape"
			" cartridge failed\n");
		if (request->op == TO_RUN)
			return tape_34xx_erp_failed(request, -EIO);
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x35:
		/*
		 * Drive equipment check. One of the following:
		 * - cu cannot recover from a drive detected error
		 * - a check code message is shown on drive display
		 * - the cartridge loader does not respond correctly
		 * - a failure occurs during an index, load, or unload cycle
		 */
		dev_warn (&device->cdev->dev, "An equipment check has occurred"
			" on the tape unit\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x36:
		if (device->cdev->id.driver_info == tape_3490)
			/* End of data. */
			return tape_34xx_erp_failed(request, -EIO);
		/* This erpa is reserved for 3480 */
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x37:
		/*
		 * Tape length error. The tape is shorter than reported in
		 * the beginning-of-tape data.
		 */
		dev_warn (&device->cdev->dev, "The tape information states an"
			" incorrect length\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x38:
		/*
		 * Physical end of tape. A read/write operation reached
		 * the physical end of tape.
		 */
		if (request->op==TO_WRI ||
		    request->op==TO_DSE ||
		    request->op==TO_WTM)
			return tape_34xx_erp_failed(request, -ENOSPC);
		return tape_34xx_erp_failed(request, -EIO);
	case 0x39:
		/* Backward at Beginning of tape. */
		return tape_34xx_erp_failed(request, -EIO);
	case 0x3a:
		/* Drive switched to not ready. */
		dev_warn (&device->cdev->dev, "The tape unit is not ready\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x3b:
		/* Manual rewind or unload. This causes an I/O error. */
		dev_warn (&device->cdev->dev, "The tape medium has been "
			"rewound or unloaded manually\n");
		tape_34xx_delete_sbid_from(device, 0);
		return tape_34xx_erp_failed(request, -EIO);
	case 0x42:
		/*
		 * Degraded mode. A condition that can cause degraded
		 * performance is detected.
		 */
		dev_warn (&device->cdev->dev, "The tape subsystem is running "
			"in degraded mode\n");
		return tape_34xx_erp_retry(request);
	case 0x43:
		/* Drive not ready. */
		tape_34xx_delete_sbid_from(device, 0);
		tape_med_state_set(device, MS_UNLOADED);
		/* Some commands commands are successful even in this case */
		if (sense[1] & SENSE_DRIVE_ONLINE) {
			switch(request->op) {
				case TO_ASSIGN:
				case TO_UNASSIGN:
				case TO_DIS:
				case TO_NOP:
					return tape_34xx_done(request);
					break;
				default:
					break;
			}
		}
		return tape_34xx_erp_failed(request, -ENOMEDIUM);
	case 0x44:
		/* Locate Block unsuccessful. */
		if (request->op != TO_BLOCK && request->op != TO_LBL)
			/* No locate block was issued. */
			return tape_34xx_erp_bug(device, request,
						 irb, sense[3]);
		return tape_34xx_erp_failed(request, -EIO);
	case 0x45:
		/* The drive is assigned to a different channel path. */
		dev_warn (&device->cdev->dev, "The tape unit is already "
			"assigned\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x46:
		/*
		 * Drive not on-line. Drive may be switched offline,
		 * the power supply may be switched off or
		 * the drive address may not be set correctly.
		 */
		dev_warn (&device->cdev->dev, "The tape unit is not online\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x47:
		/* Volume fenced. CU reports volume integrity is lost. */
		dev_warn (&device->cdev->dev, "The control unit has fenced "
			"access to the tape volume\n");
		tape_34xx_delete_sbid_from(device, 0);
		return tape_34xx_erp_failed(request, -EIO);
	case 0x48:
		/* Log sense data and retry request. */
		return tape_34xx_erp_retry(request);
	case 0x49:
		/* Bus out check. A parity check error on the bus was found. */
		dev_warn (&device->cdev->dev, "A parity error occurred on the "
			"tape bus\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x4a:
		/* Control unit erp failed. */
		dev_warn (&device->cdev->dev, "I/O error recovery failed on "
			"the tape control unit\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x4b:
		/*
		 * CU and drive incompatible. The drive requests micro-program
		 * patches, which are not available on the CU.
		 */
		dev_warn (&device->cdev->dev, "The tape unit requires a "
			"firmware update\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x4c:
		/*
		 * Recovered Check-One failure. Cu develops a hardware error,
		 * but is able to recover.
		 */
		return tape_34xx_erp_retry(request);
	case 0x4d:
		if (device->cdev->id.driver_info == tape_3490)
			/*
			 * Resetting event received. Since the driver does
			 * not support resetting event recovery (which has to
			 * be handled by the I/O Layer), retry our command.
			 */
			return tape_34xx_erp_retry(request);
		/* This erpa is reserved for 3480. */
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x4e:
		if (device->cdev->id.driver_info == tape_3490) {
			/*
			 * Maximum block size exceeded. This indicates, that
			 * the block to be written is larger than allowed for
			 * buffered mode.
			 */
			dev_warn (&device->cdev->dev, "The maximum block size"
				" for buffered mode is exceeded\n");
			return tape_34xx_erp_failed(request, -ENOBUFS);
		}
		/* This erpa is reserved for 3480. */
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x50:
		/*
		 * Read buffered log (Overflow). CU is running in extended
		 * buffered log mode, and a counter overflows. This should
		 * never happen, since we're never running in extended
		 * buffered log mode.
		 */
		return tape_34xx_erp_retry(request);
	case 0x51:
		/*
		 * Read buffered log (EOV). EOF processing occurs while the
		 * CU is in extended buffered log mode. This should never
		 * happen, since we're never running in extended buffered
		 * log mode.
		 */
		return tape_34xx_erp_retry(request);
	case 0x52:
		/* End of Volume complete. Rewind unload completed ok. */
		if (request->op == TO_RUN) {
			tape_med_state_set(device, MS_UNLOADED);
			tape_34xx_delete_sbid_from(device, 0);
			return tape_34xx_erp_succeeded(request);
		}
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	case 0x53:
		/* Global command intercept. */
		return tape_34xx_erp_retry(request);
	case 0x54:
		/* Channel interface recovery (temporary). */
		return tape_34xx_erp_retry(request);
	case 0x55:
		/* Channel interface recovery (permanent). */
		dev_warn (&device->cdev->dev, "A channel interface error cannot be"
			" recovered\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x56:
		/* Channel protocol error. */
		dev_warn (&device->cdev->dev, "A channel protocol error "
			"occurred\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x57:
		if (device->cdev->id.driver_info == tape_3480) {
			/* Attention intercept. */
			return tape_34xx_erp_retry(request);
		} else {
			/* Global status intercept. */
			return tape_34xx_erp_retry(request);
		}
	case 0x5a:
		/*
		 * Tape length incompatible. The tape inserted is too long,
		 * which could cause damage to the tape or the drive.
		 */
		dev_warn (&device->cdev->dev, "The tape unit does not support "
			"the tape length\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x5b:
		/* Format 3480 XF incompatible */
		if (sense[1] & SENSE_BEGINNING_OF_TAPE)
			/* The tape will get overwritten. */
			return tape_34xx_erp_retry(request);
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" format 3480 XF\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x5c:
		/* Format 3480-2 XF incompatible */
		dev_warn (&device->cdev->dev, "The tape unit does not support tape "
			"format 3480-2 XF\n");
		return tape_34xx_erp_failed(request, -EIO);
	case 0x5d:
		/* Tape length violation. */
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" the current tape length\n");
		return tape_34xx_erp_failed(request, -EMEDIUMTYPE);
	case 0x5e:
		/* Compaction algorithm incompatible. */
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" the compaction algorithm\n");
		return tape_34xx_erp_failed(request, -EMEDIUMTYPE);

		/* The following erpas should have been covered earlier. */
	case 0x23: /* Read data check. */
	case 0x25: /* Write data check. */
	case 0x26: /* Data check (read opposite). */
	case 0x28: /* Write id mark check. */
	case 0x31: /* Tape void. */
	case 0x40: /* Overrun error. */
	case 0x41: /* Record sequence error. */
		/* All other erpas are reserved for future use. */
	default:
		return tape_34xx_erp_bug(device, request, irb, sense[3]);
	}
}