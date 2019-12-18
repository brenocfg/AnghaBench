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
typedef  int ssize_t ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 unsigned int BEAT_NVRAM_SIZE ; 
 unsigned long BEAT_NVRW_CNT ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ beat_eeprom_write (unsigned int,unsigned long,char*) ; 

ssize_t beat_nvram_write(char *buf, size_t count, loff_t *index)
{
	unsigned int i;
	unsigned long len;
	char *p = buf;

	if (*index >= BEAT_NVRAM_SIZE)
		return -ENODEV;
	i = *index;
	if (i + count > BEAT_NVRAM_SIZE)
		count = BEAT_NVRAM_SIZE - i;

	for (; count != 0; count -= len) {
		len = count;
		if (len > BEAT_NVRW_CNT)
			len = BEAT_NVRW_CNT;
		if (beat_eeprom_write(i, len, p))
			return -EIO;

		p += len;
		i += len;
	}
	*index = i;
	return p - buf;
}