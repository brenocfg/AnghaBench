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
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  UInt8 ;
typedef  int /*<<< orphan*/ * CFURLRef ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  int /*<<< orphan*/ * CFDictionaryRef ;
typedef  int /*<<< orphan*/ * CFBundleRef ;

/* Variables and functions */
 int /*<<< orphan*/ * CFBundleCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFBundleGetInfoDictionary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFDictionaryGetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFURLCreateFromFileSystemRepresentation (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 char* convert_cfstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char const* gProgname ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBundleGetInfoStringKey ; 
 int /*<<< orphan*/  kNSHumanReadableCopyrightKey ; 
 int kxld_validate_copyright_string (char*) ; 
 int /*<<< orphan*/  printFormat () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, const char *argv[])
{
    int result = 1;
    boolean_t infoCopyrightIsValid = false;
    boolean_t readableCopyrightIsValid = false;
    CFURLRef anURL = NULL;                      // must release
    CFBundleRef aBundle = NULL;                 // must release
    CFDictionaryRef aDict = NULL;               // do not release
    CFStringRef infoCopyrightString = NULL;     // do not release
    CFStringRef readableCopyrightString = NULL; // do not release
    char *infoStr = NULL;                       // must free
    char *readableStr = NULL;                   // must free

    gProgname = argv[0];

    if (argc != 2) {
        usage();
        goto finish;
    }

    anURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault,
        (const UInt8 *) argv[1], strlen(argv[1]), /* isDirectory */ FALSE);
    if (!anURL) {
        fprintf(stderr, "Can't create path from %s\n", argv[1]);
        goto finish;
    }

    aBundle = CFBundleCreate(kCFAllocatorDefault, anURL);
    if (!aBundle) {
        fprintf(stderr, "Can't create bundle at path %s\n", argv[1]);
        goto finish;
    }

    aDict = CFBundleGetInfoDictionary(aBundle);
    if (!aDict) {
        fprintf(stderr, "Can't get info dictionary from bundle\n");
        goto finish;
    }

    infoCopyrightString = CFDictionaryGetValue(aDict, kCFBundleGetInfoStringKey);
    readableCopyrightString = CFDictionaryGetValue(aDict, kNSHumanReadableCopyrightKey);

    if (!infoCopyrightString && !readableCopyrightString) {
        fprintf(stderr, "This kext does not have a value for NSHumanReadableCopyright");
        goto finish;
    }

    if (infoCopyrightString) {
        fprintf(stderr, "Warning: This kext has a value for CFBundleGetInfoString.\n"
            "This key is obsolete, and may be removed from the kext's Info.plist.\n"
            "It has been replaced by CFBundleVersion and NSHumanReadableCopyright.\n\n");

        infoStr = convert_cfstring(infoCopyrightString);
        if (!infoStr) goto finish;

        infoCopyrightIsValid = kxld_validate_copyright_string(infoStr); 
    }

    if (readableCopyrightString) {
        readableStr = convert_cfstring(readableCopyrightString);
        if (!readableStr) goto finish;

        readableCopyrightIsValid = kxld_validate_copyright_string(readableStr);
    }

    if (!readableCopyrightIsValid) {
        if (infoCopyrightIsValid) {
            fprintf(stderr, "Warning: The copyright string in NSHumanReadableCopyright is invalid,\n"
                    "but the string in CFBundleGetInfoString is valid.  CFBundleGetInfoString is\n"
                    "obsolete.  Please migrate your copyright string to NSHumanReadableCopyright.\n\n");
        } else {
            fprintf(stderr, "Error: There is no valid copyright string for this kext.\n\n");
            printFormat(); 
            goto finish;
        }
    }

    result = 0;
finish:
    if (anURL) CFRelease(anURL);
    if (aBundle) CFRelease(aBundle);
    if (infoStr) free(infoStr);
    if (readableStr) free(readableStr);

    return result;
}