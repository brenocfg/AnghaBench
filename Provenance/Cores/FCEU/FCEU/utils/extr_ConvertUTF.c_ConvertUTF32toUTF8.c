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
typedef  int /*<<< orphan*/  UTF8 ;
typedef  scalar_t__ UTF32 ;
typedef  int /*<<< orphan*/  ConversionResult ;
typedef  scalar_t__ ConversionFlags ;

/* Variables and functions */
 scalar_t__ UNI_MAX_LEGAL_UTF32 ; 
 scalar_t__ UNI_REPLACEMENT_CHAR ; 
 scalar_t__ UNI_SUR_HIGH_START ; 
 scalar_t__ UNI_SUR_LOW_END ; 
 int /*<<< orphan*/  conversionOK ; 
 scalar_t__* firstByteMark ; 
 int /*<<< orphan*/  sourceIllegal ; 
 scalar_t__ strictConversion ; 
 int /*<<< orphan*/  targetExhausted ; 

ConversionResult ConvertUTF32toUTF8 (
	const UTF32** sourceStart, const UTF32* sourceEnd, 
	UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF32* source = *sourceStart;
    UTF8* target = *targetStart;
    while (source < sourceEnd) {
	UTF32 ch;
	unsigned short bytesToWrite = 0;
	const UTF32 byteMask = 0xBF;
	const UTF32 byteMark = 0x80; 
	ch = *source++;
	if (flags == strictConversion ) {
	    /* UTF-16 surrogate values are illegal in UTF-32 */
	    if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		--source; /* return to the illegal value itself */
		result = sourceIllegal;
		break;
	    }
	}
	/*
	 * Figure out how many bytes the result will require. Turn any
	 * illegally large UTF32 things (> Plane 17) into replacement chars.
	 */
	if (ch < (UTF32)0x80) {	     bytesToWrite = 1;
	} else if (ch < (UTF32)0x800) {     bytesToWrite = 2;
	} else if (ch < (UTF32)0x10000) {   bytesToWrite = 3;
	} else if (ch <= UNI_MAX_LEGAL_UTF32) {  bytesToWrite = 4;
	} else {			    bytesToWrite = 3;
					    ch = UNI_REPLACEMENT_CHAR;
					    result = sourceIllegal;
	}
	
	target += bytesToWrite;
	if (target > targetEnd) {
	    --source; /* Back up source pointer! */
	    target -= bytesToWrite; result = targetExhausted; break;
	}
	switch (bytesToWrite) { /* note: everything falls through. */
	    case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
	    case 1: *--target = (UTF8) (ch | firstByteMark[bytesToWrite]);
	}
	target += bytesToWrite;
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}