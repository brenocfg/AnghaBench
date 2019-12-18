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
typedef  scalar_t__ CFTypeRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetCString (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IOIteratorNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOObjectRelease (scalar_t__) ; 
 scalar_t__ IORegistryEntryCreateCFProperty (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOServiceGetMatchingServices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOServiceMatching (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int hCDROM ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBooleanTrue ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kIOBSDNameKey ; 
 int /*<<< orphan*/  kIOCDMediaClass ; 
 int /*<<< orphan*/  kIOMasterPortDefault ; 
 int /*<<< orphan*/  kIOMediaEjectableKey ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int MacOSXCDInit(const char * useless_for_now)
{
	CFMutableDictionaryRef  classesToMatch;
	io_iterator_t mediaIterator;
	io_object_t media;
	char cdrom_name[ MAXPATHLEN ];

	classesToMatch = IOServiceMatching(kIOCDMediaClass); 
	CFDictionarySetValue(classesToMatch, CFSTR(kIOMediaEjectableKey),
		kCFBooleanTrue); 
	IOServiceGetMatchingServices(kIOMasterPortDefault,
		classesToMatch, &mediaIterator);    

	media = IOIteratorNext(mediaIterator);
	
	if(media)
	{
		CFTypeRef path;

		path = IORegistryEntryCreateCFProperty(media,
			CFSTR(kIOBSDNameKey),
			kCFAllocatorDefault, 0);

		if (path)
		{
			size_t length;

			strcpy(cdrom_name, _PATH_DEV);
			strcat(cdrom_name, "r");
			length = strlen(cdrom_name);

			CFStringGetCString(path, cdrom_name + length,
				MAXPATHLEN - length, kCFStringEncodingUTF8);

			CFRelease(path);
		}
		IOObjectRelease(media);
	}

	if ((hCDROM = open(cdrom_name, O_RDONLY)) == -1)
	{
		return -1;
	}

	return 0;
}