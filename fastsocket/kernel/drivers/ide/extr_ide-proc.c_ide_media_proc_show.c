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
struct seq_file {scalar_t__ private; } ;
struct TYPE_2__ {int media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
#define  ide_cdrom 132 
#define  ide_disk 131 
#define  ide_floppy 130 
#define  ide_optical 129 
#define  ide_tape 128 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const*) ; 

__attribute__((used)) static int ide_media_proc_show(struct seq_file *m, void *v)
{
	ide_drive_t	*drive = (ide_drive_t *) m->private;
	const char	*media;

	switch (drive->media) {
	case ide_disk:		media = "disk\n";	break;
	case ide_cdrom:		media = "cdrom\n";	break;
	case ide_tape:		media = "tape\n";	break;
	case ide_floppy:	media = "floppy\n";	break;
	case ide_optical:	media = "optical\n";	break;
	default:		media = "UNKNOWN\n";	break;
	}
	seq_puts(m, media);
	return 0;
}