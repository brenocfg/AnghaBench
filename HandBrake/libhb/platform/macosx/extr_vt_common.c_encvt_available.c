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
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  scalar_t__ CFIndex ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 scalar_t__ CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CFDictionaryGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CFEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTCopyVideoEncoderList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kVTVideoEncoderSpecification_EncoderID ; 

int encvt_available(CFStringRef encoder)
{
    CFArrayRef encoder_list;
    VTCopyVideoEncoderList(NULL, &encoder_list);
    CFIndex size = CFArrayGetCount(encoder_list);

    for (CFIndex i = 0; i < size; i++ )
    {
        CFDictionaryRef encoder_dict = CFArrayGetValueAtIndex(encoder_list, i);
        CFStringRef encoder_id = CFDictionaryGetValue(encoder_dict, kVTVideoEncoderSpecification_EncoderID);
        if (CFEqual(encoder_id, encoder))
        {
            CFRelease(encoder_list);
            return 1;
        }
    }
    CFRelease(encoder_list);
    return 0;
}