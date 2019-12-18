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
 unsigned char ROW25_COLUMN4_HOUR_UNITS ; 
 unsigned char ROW25_COLUMN5_HOUR_TENS ; 

__attribute__((used)) static inline int saa5246a_extract_hour_from_infobits(
    unsigned char infobits[10])
{
	int hour_tens, hour_units;

	hour_units = infobits[4] & ROW25_COLUMN4_HOUR_UNITS;
	hour_tens  = infobits[5] & ROW25_COLUMN5_HOUR_TENS;

	return((hour_tens << 4) | hour_units);
}