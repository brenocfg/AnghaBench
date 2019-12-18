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
typedef  scalar_t__ UTF32 ;
typedef  scalar_t__ UTF16 ;
typedef  scalar_t__ ConversionResult ;
typedef  scalar_t__ ConversionFlags ;

/* Variables and functions */
 scalar_t__ UNI_SUR_HIGH_END ; 
 scalar_t__ UNI_SUR_HIGH_START ; 
 scalar_t__ UNI_SUR_LOW_END ; 
 scalar_t__ UNI_SUR_LOW_START ; 
 scalar_t__ conversionOK ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ halfBase ; 
 scalar_t__ halfShift ; 
 scalar_t__ sourceExhausted ; 
 scalar_t__ sourceIllegal ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strictConversion ; 
 scalar_t__ targetExhausted ; 

ConversionResult ConvertUTF16toUTF32 (
	const UTF16** sourceStart, const UTF16* sourceEnd, 
	UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
    ConversionResult result = conversionOK;
    const UTF16* source = *sourceStart;
    UTF32* target = *targetStart;
    UTF32 ch, ch2;
    while (source < sourceEnd) {
	const UTF16* oldSource = source; /*  In case we have to back up because of target overflow. */
	ch = *source++;
	/* If we have a surrogate pair, convert to UTF32 first. */
	if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
	    /* If the 16 bits following the high surrogate are in the source buffer... */
	    if (source < sourceEnd) {
		ch2 = *source;
		/* If it's a low surrogate, convert to UTF32. */
		if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
		    ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
			+ (ch2 - UNI_SUR_LOW_START) + halfBase;
		    ++source;
		} else if (flags == strictConversion) { /* it's an unpaired high surrogate */
		    --source; /* return to the illegal value itself */
		    result = sourceIllegal;
		    break;
		}
	    } else { /* We don't have the 16 bits following the high surrogate. */
		--source; /* return to the high surrogate */
		result = sourceExhausted;
		break;
	    }
	} else if (flags == strictConversion) {
	    /* UTF-16 surrogate values are illegal in UTF-32 */
	    if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
		--source; /* return to the illegal value itself */
		result = sourceIllegal;
		break;
	    }
	}
	if (target >= targetEnd) {
	    source = oldSource; /* Back up source pointer! */
	    result = targetExhausted; break;
	}
	*target++ = ch;
    }
    *sourceStart = source;
    *targetStart = target;
#ifdef CVTUTF_DEBUG
if (result == sourceIllegal) {
    fprintf(stderr, "ConvertUTF16toUTF32 illegal seq 0x%04x,%04x\n", ch, ch2);
    fflush(stderr);
}
#endif
    return result;
}