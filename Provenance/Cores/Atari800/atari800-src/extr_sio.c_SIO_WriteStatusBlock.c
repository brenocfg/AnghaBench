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
 int /*<<< orphan*/  Log_print (char*,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const,int const) ; 
 scalar_t__ SIO_OFF ; 
 scalar_t__* SIO_drive_status ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 

int SIO_WriteStatusBlock(int unit, const UBYTE *buffer)
{
	int size;
#ifdef DEBUG
	Log_print("Write Status-Block: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
		buffer[0], buffer[1], buffer[2], buffer[3],
		buffer[4], buffer[5], buffer[6], buffer[7],
		buffer[8], buffer[9], buffer[10], buffer[11]);
#endif
	if (SIO_drive_status[unit] == SIO_OFF)
		return 0;
	/* We only care about the density and the sector count here.
	   Setting everything else right here seems to be non-sense.
	   I'm not sure about this density settings, my XF551
	   honors only the sector size and ignores the density */
	size = buffer[6] * 256 + buffer[7];
	if (size == 128 || size == 256)
		SIO_format_sectorsize[unit] = size;
	/* Note that the number of heads are minus 1 */
	SIO_format_sectorcount[unit] = buffer[0] * (buffer[2] * 256 + buffer[3]) * (buffer[4] + 1);
	if (SIO_format_sectorcount[unit] < 1 || SIO_format_sectorcount[unit] > 65535)
		SIO_format_sectorcount[unit] = 720;
	return 'C';
}