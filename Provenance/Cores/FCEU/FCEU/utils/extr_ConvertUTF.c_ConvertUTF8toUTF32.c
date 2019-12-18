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
typedef  size_t UTF8 ;
typedef  int UTF32 ;
typedef  int /*<<< orphan*/  ConversionResult ;
typedef  scalar_t__ ConversionFlags ;

/* Variables and functions */
 int UNI_MAX_LEGAL_UTF32 ; 
 void* UNI_REPLACEMENT_CHAR ; 
 int UNI_SUR_HIGH_START ; 
 int UNI_SUR_LOW_END ; 
 int /*<<< orphan*/  conversionOK ; 
 int /*<<< orphan*/  isLegalUTF8 (size_t const*,unsigned short) ; 
 int* offsetsFromUTF8 ; 
 int /*<<< orphan*/  sourceExhausted ; 
 int /*<<< orphan*/  sourceIllegal ; 
 scalar_t__ strictConversion ; 
 int /*<<< orphan*/  targetExhausted ; 
 unsigned short* trailingBytesForUTF8 ; 

ConversionResult ConvertUTF8toUTF32 (
	const UTF8** sourceStart, const UTF8* sourceEnd, 
	UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF8* source = *sourceStart;
    UTF32* target = *targetStart;
    while (source < sourceEnd) {
	UTF32 ch = 0;
	unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
	if (source + extraBytesToRead >= sourceEnd) {
	    result = sourceExhausted; break;
	}
	/* Do this check whether lenient or strict */
	if (! isLegalUTF8(source, extraBytesToRead+1)) {
	    result = sourceIllegal;
	    break;
	}
	/*
	 * The cases all fall through. See "Note A" below.
	 */
	switch (extraBytesToRead) {
	    case 5: ch += *source++; ch <<= 6;
	    case 4: ch += *source++; ch <<= 6;
	    case 3: ch += *source++; ch <<= 6;
	    case 2: ch += *source++; ch <<= 6;
	    case 1: ch += *source++; ch <<= 6;
	    case 0: ch += *source++;
	}
	ch -= offsetsFromUTF8[extraBytesToRead];

	if (target >= targetEnd) {
	    source -= (extraBytesToRead+1); /* Back up the source pointer! */
	    result = targetExhausted; break;
	}
	if (ch <= UNI_MAX_LEGAL_UTF32) {
	    /*
	     * UTF-16 surrogate values are illegal in UTF-32, and anything
	     * over Plane 17 (> 0x10FFFF) is illegal.
	     */
	    if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		if (flags == strictConversion) {
		    source -= (extraBytesToRead+1); /* return to the illegal value itself */
		    result = sourceIllegal;
		    break;
		} else {
		    *target++ = UNI_REPLACEMENT_CHAR;
		}
	    } else {
		*target++ = ch;
	    }
	} else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
	    result = sourceIllegal;
	    *target++ = UNI_REPLACEMENT_CHAR;
	}
    }
    *sourceStart = source;
    *targetStart = target;
    return result;
}