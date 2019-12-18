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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
#define  DID_NEXUS_FAILURE 130 
 int /*<<< orphan*/  DID_OK ; 
#define  DID_TARGET_FAILURE 129 
#define  DID_TRANSPORT_FAILFAST 128 
 int EBADE ; 
 int EIO ; 
 int ENOLINK ; 
 int EREMOTEIO ; 
 int host_byte (int) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __scsi_error_from_host_byte(struct scsi_cmnd *cmd, int result)
{
	int error = 0;

	switch(host_byte(result)) {
	case DID_TRANSPORT_FAILFAST:
		error = -ENOLINK;
		break;
	case DID_TARGET_FAILURE:
		set_host_byte(cmd, DID_OK);
		error = -EREMOTEIO;
		break;
	case DID_NEXUS_FAILURE:
		set_host_byte(cmd, DID_OK);
		error = -EBADE;
		break;
	default:
		error = -EIO;
		break;
	}

	return error;
}