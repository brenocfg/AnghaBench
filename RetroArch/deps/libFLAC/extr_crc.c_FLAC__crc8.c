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
typedef  size_t FLAC__uint8 ;
typedef  int /*<<< orphan*/  FLAC__byte ;

/* Variables and functions */
 size_t* FLAC__crc8_table ; 

FLAC__uint8 FLAC__crc8(const FLAC__byte *data, unsigned len)
{
	FLAC__uint8 crc = 0;

	while(len--)
		crc = FLAC__crc8_table[crc ^ *data++];

	return crc;
}