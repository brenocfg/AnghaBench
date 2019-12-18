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
typedef  int /*<<< orphan*/  versBuffer ;
typedef  int OSKextVersion ;
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 scalar_t__ CFStringGetCString (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int OSKextParseVersionString (char*) ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 int kOSKextVersionMaxLength ; 

OSKextVersion OSKextParseVersionCFString(CFStringRef versionString)
{
    OSKextVersion result = -1;
    char         versBuffer[kOSKextVersionMaxLength];
    
    if (CFStringGetCString(versionString, versBuffer,
        sizeof(versBuffer), kCFStringEncodingASCII)) {

        result = OSKextParseVersionString(versBuffer);
    }
    return result;
}