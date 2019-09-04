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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int* num2hex ; 

uint16_t TEXT_numToHexString(uint8_t *buf, uint32_t value, int16_t bufSize, uint8_t minLen, uint8_t padChar) {
	uint8_t work[10];
	uint8_t count = 0;
	uint8_t i;

	if(minLen > bufSize || minLen > 10)
		return 0;

	do {
		work[count++] = num2hex[ value & 0xF ];
		value >>= 4;
	} while(value != 0);

	if(count > bufSize)
		return 0;

	while( count < minLen )
		work[count++] = padChar;

	for( i = 0; i < count; i++)
		buf[i] = work[count-1-i];

	return count;
}