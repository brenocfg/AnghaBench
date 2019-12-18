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
struct atari_format_descr {int track; int head; int sect_offset; } ;
struct TYPE_5__ {int blocks; int spt; } ;
struct TYPE_4__ {scalar_t__ drive_types; int index; } ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int BufferDrive ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ DriveType ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FILL (int,int) ; 
 scalar_t__ FormatError ; 
 int /*<<< orphan*/  IRQ_MFP_FDC ; 
 int IsFormatting ; 
 int NUM_DISK_MINORS ; 
 int ReqSide ; 
 int ReqTrack ; 
 unsigned char* TrackBuffer ; 
 TYPE_2__* UDT ; 
 TYPE_2__* atari_disk_type ; 
 int /*<<< orphan*/  atari_turnon_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fd_action (int) ; 
 int fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 int /*<<< orphan*/  floppy_irq ; 
 int /*<<< orphan*/  format_wait ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__* minor2disktype ; 
 int /*<<< orphan*/  motor_off_timer ; 
 int /*<<< orphan*/  redo_fd_request () ; 
 int /*<<< orphan*/  sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_format(int drive, int type, struct atari_format_descr *desc)
{
	unsigned char	*p;
	int sect, nsect;
	unsigned long	flags;

	DPRINT(("do_format( dr=%d tr=%d he=%d offs=%d )\n",
		drive, desc->track, desc->head, desc->sect_offset ));

	local_irq_save(flags);
	while( fdc_busy ) sleep_on( &fdc_wait );
	fdc_busy = 1;
	stdma_lock(floppy_irq, NULL);
	atari_turnon_irq( IRQ_MFP_FDC ); /* should be already, just to be sure */
	local_irq_restore(flags);

	if (type) {
		if (--type >= NUM_DISK_MINORS ||
		    minor2disktype[type].drive_types > DriveType) {
			redo_fd_request();
			return -EINVAL;
		}
		type = minor2disktype[type].index;
		UDT = &atari_disk_type[type];
	}

	if (!UDT || desc->track >= UDT->blocks/UDT->spt/2 || desc->head >= 2) {
		redo_fd_request();
		return -EINVAL;
	}

	nsect = UDT->spt;
	p = TrackBuffer;
	/* The track buffer is used for the raw track data, so its
	   contents become invalid! */
	BufferDrive = -1;
	/* stop deselect timer */
	del_timer( &motor_off_timer );

	FILL( 60 * (nsect / 9), 0x4e );
	for( sect = 0; sect < nsect; ++sect ) {
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfe;
		*p++ = desc->track;
		*p++ = desc->head;
		*p++ = (nsect + sect - desc->sect_offset) % nsect + 1;
		*p++ = 2;
		*p++ = 0xf7;
		FILL( 22, 0x4e );
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfb;
		FILL( 512, 0xe5 );
		*p++ = 0xf7;
		FILL( 40, 0x4e );
	}
	FILL( TrackBuffer+BUFFER_SIZE-p, 0x4e );

	IsFormatting = 1;
	FormatError = 0;
	ReqTrack = desc->track;
	ReqSide  = desc->head;
	do_fd_action( drive );

	sleep_on( &format_wait );

	redo_fd_request();
	return( FormatError ? -EIO : 0 );	
}