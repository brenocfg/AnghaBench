#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buttons_count; int /*<<< orphan*/  buttons; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ joydata_t ;
typedef  int /*<<< orphan*/  joy_elemdata_t ;
typedef  int /*<<< orphan*/  io_object_t ;
typedef  scalar_t__ SInt32 ;
typedef  scalar_t__ CFTypeRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;

/* Variables and functions */
 scalar_t__ CFDictionaryGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetCString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IORegistryEntryCreateCFProperties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  joy_cmp_buttons ; 
 int joy_count ; 
 int /*<<< orphan*/  joy_create_interface (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  joy_find_elements (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* joys ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberSInt32Type ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 scalar_t__ kHIDPage_GenericDesktop ; 
 scalar_t__ kHIDUsage_GD_GamePad ; 
 scalar_t__ kHIDUsage_GD_Joystick ; 
 int /*<<< orphan*/  kIOHIDPrimaryUsageKey ; 
 int /*<<< orphan*/  kIOHIDPrimaryUsagePageKey ; 
 int /*<<< orphan*/  kIOHIDProductKey ; 
 int /*<<< orphan*/  kNilOptions ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* realloc (TYPE_1__*,int) ; 

__attribute__((used)) static void joy_read_device(io_object_t dev)    {
    CFMutableDictionaryRef props = 0;

    /* Create a dictionary to read the device's properties. */
    if(IORegistryEntryCreateCFProperties(dev, &props, kCFAllocatorDefault,
                                         kNilOptions) == KERN_SUCCESS)  {
        CFTypeRef inf;
        SInt32 page, usage;
        void *ptr;

        /* Grab the primary usage page of the device. */
        inf = CFDictionaryGetValue(props, CFSTR(kIOHIDPrimaryUsagePageKey));

        if(!inf || !CFNumberGetValue((CFNumberRef)inf, kCFNumberSInt32Type,
                                     &page))    {
            goto out;
        }

        /* Ignore devices that are not in the Generic Desktop page. */
        if(page != kHIDPage_GenericDesktop) {
            goto out;
        }

        /* Grab the primary device usage. */
        inf = CFDictionaryGetValue(props, CFSTR(kIOHIDPrimaryUsageKey));

        if(!inf || !CFNumberGetValue((CFNumberRef)inf, kCFNumberSInt32Type,
                                     &usage))   {
            goto out;
        }

        /* Ignore devices that are not either a Game Pad or Joystick. */
        if(usage != kHIDUsage_GD_GamePad && usage != kHIDUsage_GD_Joystick) {
            goto out;
        }

        /* Allocate space for the new joystick structure. */
        ptr = realloc(joys, (joy_count + 1) * sizeof(joydata_t));

        if(ptr == NULL) {
            goto out;
        }

        joys = (joydata_t *)ptr;
        memset(joys + joy_count, 0, sizeof(joydata_t));

        /* Grab and store the name of the device. */
        inf = CFDictionaryGetValue(props, CFSTR(kIOHIDProductKey));

        if(!CFStringGetCString((CFStringRef)inf, joys[joy_count].name, 256,
                               kCFStringEncodingUTF8))  {
            goto out;
        }

        /* Create the device interface needed to interact with the device. */
        if(!joy_create_interface(dev, joys + joy_count))    {
            goto out;
        }

        /* Find all elements of the device. */
        joy_find_elements(props, joys + joy_count);

        qsort(joys[joy_count].buttons, joys[joy_count].buttons_count,
              sizeof(joy_elemdata_t), &joy_cmp_buttons);

        ++joy_count;
    }

out:
    CFRelease(props);
}