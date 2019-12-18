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

/* Variables and functions */
 int CS_CDHASH_LEN ; 
 int CS_CDHASH_STRING_SIZE ; 

__attribute__((used)) static void cdhash_to_string(char str[CS_CDHASH_STRING_SIZE], uint8_t const * const cdhash) {
	   static char const nibble[] = "0123456789abcdef";

	   /* Apparently still the safest way to get a hex representation
		* of binary data.
		* xnu's printf routines have %*D/%20D in theory, but "not really", see:
		* <rdar://problem/33328859> confusion around %*D/%nD in printf
		*/
	   for (int i = 0; i < CS_CDHASH_LEN; ++i) {
			   str[i*2] = nibble[(cdhash[i] & 0xf0) >> 4];
			   str[i*2+1] = nibble[cdhash[i] & 0x0f];
	   }
	   str[CS_CDHASH_STRING_SIZE - 1] = 0;
}