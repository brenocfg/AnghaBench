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
typedef  int ushort ;

/* Variables and functions */
 unsigned char* mfmdecode ; 

__attribute__((used)) static inline unsigned char dos_decode_byte(ushort word)
{
	register ushort w2;
	register unsigned char byte;
	register unsigned char *dec = mfmdecode;

	w2=word;
	w2>>=8;
	w2&=127;
	byte = dec[w2];
	byte <<= 4;
	w2 = word & 127;
	byte |= dec[w2];
	return byte;
}