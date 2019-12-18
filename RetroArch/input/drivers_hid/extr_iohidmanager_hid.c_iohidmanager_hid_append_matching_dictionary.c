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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;
typedef  int /*<<< orphan*/  CFMutableArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayAppendValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFDictionaryCreateMutable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberIntType ; 
 int /*<<< orphan*/  kCFTypeDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kIOHIDDeviceUsageKey ; 
 int /*<<< orphan*/  kIOHIDDeviceUsagePageKey ; 

__attribute__((used)) static void iohidmanager_hid_append_matching_dictionary(
      CFMutableArrayRef array,
      uint32_t page, uint32_t use)
{
   CFMutableDictionaryRef matcher = CFDictionaryCreateMutable(
         kCFAllocatorDefault, 0,
         &kCFTypeDictionaryKeyCallBacks,
         &kCFTypeDictionaryValueCallBacks);
   CFNumberRef pagen = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &page);
   CFNumberRef usen  = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &use);

   CFDictionarySetValue(matcher, CFSTR(kIOHIDDeviceUsagePageKey), pagen);
   CFDictionarySetValue(matcher, CFSTR(kIOHIDDeviceUsageKey), usen);
   CFArrayAppendValue(array, matcher);

   CFRelease(pagen);
   CFRelease(usen);
   CFRelease(matcher);
}