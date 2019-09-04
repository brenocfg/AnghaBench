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
typedef  int /*<<< orphan*/  unicode_mappings32 ;
typedef  int /*<<< orphan*/  unicode_mappings16 ;
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 scalar_t__ HANGUL_LBASE ; 
 scalar_t__ HANGUL_LCOUNT ; 
 scalar_t__ HANGUL_SBASE ; 
 scalar_t__ HANGUL_SCOUNT ; 
 scalar_t__ HANGUL_TBASE ; 
 scalar_t__ HANGUL_TCOUNT ; 
 scalar_t__ HANGUL_VBASE ; 
 scalar_t__ HANGUL_VCOUNT ; 
 scalar_t__ __CFUniCharBMPPrecompDestinationTable ; 
 scalar_t__ __CFUniCharPrecompSourceTable ; 
 int /*<<< orphan*/  __CFUniCharPrecompositionTableLength ; 
 int getmappedvalue16 (int /*<<< orphan*/  const*,int,scalar_t__) ; 
 int getmappedvalue32 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u_int16_t
unicode_combine(u_int16_t base, u_int16_t combining)
{
	u_int32_t value;

	/* Check HANGUL */
	if ((combining >= HANGUL_VBASE) && (combining < (HANGUL_TBASE + HANGUL_TCOUNT))) {
		/* 2 char Hangul sequences */
		if ((combining < (HANGUL_VBASE + HANGUL_VCOUNT)) &&
		    (base >= HANGUL_LBASE && base < (HANGUL_LBASE + HANGUL_LCOUNT))) {
		    return (HANGUL_SBASE +
		            ((base - HANGUL_LBASE)*(HANGUL_VCOUNT*HANGUL_TCOUNT)) +
		            ((combining  - HANGUL_VBASE)*HANGUL_TCOUNT));
		}
	
		/* 3 char Hangul sequences */
		if ((combining > HANGUL_TBASE) &&
		    (base >= HANGUL_SBASE && base < (HANGUL_SBASE + HANGUL_SCOUNT))) {
			if ((base - HANGUL_SBASE) % HANGUL_TCOUNT)
				return (0);
			else
				return (base + (combining - HANGUL_TBASE));
		}
	}

	value = getmappedvalue32(
		(const unicode_mappings32 *)__CFUniCharPrecompSourceTable,
		__CFUniCharPrecompositionTableLength, combining);

	if (value) {
		value = getmappedvalue16(
			(const unicode_mappings16 *)
			((const u_int32_t *)__CFUniCharBMPPrecompDestinationTable + (value & 0xFFFF)),
			(value >> 16), base);
	}
	return (value);
}