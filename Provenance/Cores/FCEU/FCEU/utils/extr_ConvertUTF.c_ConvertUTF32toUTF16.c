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
typedef  int UTF32 ;
typedef  void* UTF16 ;
typedef  int /*<<< orphan*/  ConversionResult ;
typedef  scalar_t__ ConversionFlags ;

/* Variables and functions */
 int UNI_MAX_BMP ; 
 int UNI_MAX_LEGAL_UTF32 ; 
 void* UNI_REPLACEMENT_CHAR ; 
 int UNI_SUR_HIGH_START ; 
 int UNI_SUR_LOW_END ; 
 scalar_t__ UNI_SUR_LOW_START ; 
 int /*<<< orphan*/  conversionOK ; 
 scalar_t__ halfBase ; 
 int halfMask ; 
 int halfShift ; 
 int /*<<< orphan*/  sourceIllegal ; 
 scalar_t__ strictConversion ; 
 int /*<<< orphan*/  targetExhausted ; 

ConversionResult ConvertUTF32toUTF16 (
	const UTF32** sourceStart, const UTF32* sourceEnd, 
	UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF32* source = *sourceStart;
    UTF16* target = *targetStart;
    while (source < sourceEnd) {
	UTF32 ch;
	if (target >= targetEnd) {
	    result = targetExhausted; break;
	}
	ch = *source++;
	if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
	    /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
	    if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		if (flags == strictConversion) {
		    --source; /* return to the illegal value itself */
		    result = sourceIllegal;
		    break;
		} else {
		    *target++ = UNI_REPLACEMENT_CHAR;
		}
	    } else {
		*target++ = (UTF16)ch; /* normal case */
	    }
	} else if (ch > UNI_MAX_LEGAL_UTF32) {
	    if (flags == strictConversion) {
		result = sourceIllegal;
	    } else {
		*target++ = UNI_REPLACEMENT_CHAR;
	    }
	} else {
	    /* target is a character in range 0xFFFF - 0x10FFFF. */
	    if (target + 1 >= targetEnd) {
		--source; /* Back up source pointer! */
		result = targetExhausted; break;
	    }
	    ch -= halfBase;
	    *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
	    *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
	}
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}