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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ SIO_OFF ; 
 scalar_t__* SIO_drive_status ; 
 int* sectorcount ; 
 int* sectorsize ; 

int SIO_ReadStatusBlock(int unit, UBYTE *buffer)
{
	UBYTE tracks;
	UBYTE heads;
	int spt;
	if (SIO_drive_status[unit] == SIO_OFF)
		return 0;
	/* default to 1 track, 1 side for non-standard images */
	tracks = 1;
	heads = 1;
	spt = sectorcount[unit];

	if (spt % 40 == 0) {
		/* standard disk */
		tracks = 40;
		spt /= 40;
		if (spt > 26 && spt % 2 == 0) {
			/* double-sided */
			heads = 2;
			spt >>= 1;
			if (spt > 26 && spt % 2 == 0) {
				/* double-sided, 80 tracks */
				tracks = 80;
				spt >>= 1;
			}
		}
	}

	buffer[0] = tracks;              /* # of tracks */
	buffer[1] = 1;                   /* step rate */
	buffer[2] = (UBYTE) (spt >> 8);  /* sectors per track. HI byte */
	buffer[3] = (UBYTE) spt;         /* sectors per track. LO byte */
	buffer[4] = (UBYTE) (heads - 1); /* # of heads minus 1 */
	/* FM for single density, MFM otherwise */
	buffer[5] = (sectorsize[unit] == 128 && sectorcount[unit] <= 720) ? 0 : 4;
	buffer[6] = (UBYTE) (sectorsize[unit] >> 8); /* bytes per sector. HI byte */
	buffer[7] = (UBYTE) sectorsize[unit];        /* bytes per sector. LO byte */
	buffer[8] = 1;                   /* drive is online */
	buffer[9] = 192;                 /* transfer speed, whatever this means */
	buffer[10] = 0;
	buffer[11] = 0;
	return 'C';
}