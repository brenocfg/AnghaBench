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
typedef  scalar_t__ io_object_t ;
typedef  int /*<<< orphan*/  io_iterator_t ;
typedef  int /*<<< orphan*/  UInt8 ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;
typedef  int /*<<< orphan*/  CFDataRef ;
typedef  int /*<<< orphan*/  CDTOC ;

/* Variables and functions */
 int /*<<< orphan*/  CFDataGetBytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDataGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRangeMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IOIteratorNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOObjectRelease (scalar_t__) ; 
 int /*<<< orphan*/  IORegistryEntryCreateCFProperty (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOServiceGetMatchingServices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOServiceMatching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBooleanTrue ; 
 int /*<<< orphan*/  kIOCDMediaClass ; 
 int /*<<< orphan*/  kIOCDMediaTOCKey ; 
 int /*<<< orphan*/  kIOMasterPortDefault ; 
 int /*<<< orphan*/  kIOMediaEjectableKey ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CDTOC * GetTOCFromCDPath(void)
{
	CFMutableDictionaryRef  classesToMatch;
	io_iterator_t mediaIterator;
	io_object_t media;
	CDTOC * TOC = NULL;

	classesToMatch = IOServiceMatching(kIOCDMediaClass); 
	CFDictionarySetValue(classesToMatch, CFSTR(kIOMediaEjectableKey),
		kCFBooleanTrue); 
	IOServiceGetMatchingServices(kIOMasterPortDefault,
		classesToMatch, &mediaIterator);    

	media = IOIteratorNext(mediaIterator);
	
	if(media)
	{
		CFDataRef TOCData = IORegistryEntryCreateCFProperty(media, CFSTR(kIOCDMediaTOCKey), kCFAllocatorDefault, 0);
		TOC = malloc(CFDataGetLength(TOCData));
		CFDataGetBytes(TOCData,CFRangeMake(0,CFDataGetLength(TOCData)),(UInt8 *)TOC);
		CFRelease(TOCData);
		IOObjectRelease(media);
	}
	
	return TOC;
}