#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned char TYPE_DISK ; 
 unsigned char TYPE_MEDIUM_CHANGER ; 
 unsigned char TYPE_MOD ; 
 unsigned char TYPE_PROCESSOR ; 
 unsigned char TYPE_ROM ; 
 unsigned char TYPE_SCANNER ; 
 unsigned char TYPE_TAPE ; 
 unsigned char TYPE_WORM ; 
 int /*<<< orphan*/  device_inquiry (struct Scsi_Host*,int) ; 
 TYPE_1__* ld (struct Scsi_Host*) ; 
 scalar_t__ read_capacity (struct Scsi_Host*,int) ; 

__attribute__((used)) static int device_exists(struct Scsi_Host *shpnt, int ldn, int *block_length, int *device_type)
{
	unsigned char *buf;
	/* if no valid device found, return immediately with 0 */
	if (!(device_inquiry(shpnt, ldn)))
		return 0;
	buf = (unsigned char *) (&(ld(shpnt)[ldn].buf));
	if (*buf == TYPE_ROM) {
		*device_type = TYPE_ROM;
		*block_length = 2048;	/* (standard blocksize for yellow-/red-book) */
		return 1;
	}
	if (*buf == TYPE_WORM) {
		*device_type = TYPE_WORM;
		*block_length = 2048;
		return 1;
	}
	if (*buf == TYPE_DISK) {
		*device_type = TYPE_DISK;
		if (read_capacity(shpnt, ldn)) {
			*block_length = *(buf + 7) + (*(buf + 6) << 8) + (*(buf + 5) << 16) + (*(buf + 4) << 24);
			return 1;
		} else
			return 0;
	}
	if (*buf == TYPE_MOD) {
		*device_type = TYPE_MOD;
		if (read_capacity(shpnt, ldn)) {
			*block_length = *(buf + 7) + (*(buf + 6) << 8) + (*(buf + 5) << 16) + (*(buf + 4) << 24);
			return 1;
		} else
			return 0;
	}
	if (*buf == TYPE_TAPE) {
		*device_type = TYPE_TAPE;
		*block_length = 0;	/* not in use (setting by mt and mtst in op.) */
		return 1;
	}
	if (*buf == TYPE_PROCESSOR) {
		*device_type = TYPE_PROCESSOR;
		*block_length = 0;	/* they set their stuff on drivers */
		return 1;
	}
	if (*buf == TYPE_SCANNER) {
		*device_type = TYPE_SCANNER;
		*block_length = 0;	/* they set their stuff on drivers */
		return 1;
	}
	if (*buf == TYPE_MEDIUM_CHANGER) {
		*device_type = TYPE_MEDIUM_CHANGER;
		*block_length = 0;	/* One never knows, what to expect on a medium
					   changer device. */
		return 1;
	}
	return 0;
}