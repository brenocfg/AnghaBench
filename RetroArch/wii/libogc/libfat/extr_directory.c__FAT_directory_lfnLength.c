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

/* Variables and functions */
 unsigned char ABOVE_UCS_RANGE ; 
 int /*<<< orphan*/  ILLEGAL_LFN_CHARACTERS ; 
 int MAX_LFN_LENGTH ; 
 size_t NAME_MAX ; 
 int mbsrtowcs (int /*<<< orphan*/ *,char const**,int,int /*<<< orphan*/ *) ; 
 size_t strnlen (char const*,size_t) ; 
 int /*<<< orphan*/ * strpbrk (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _FAT_directory_lfnLength (const char* name) {
	unsigned int i;
	size_t nameLength;
	int ucsLength;
	const char* tempName = name;

	nameLength = strnlen(name, NAME_MAX);
	// Make sure the name is short enough to be valid
	if ( nameLength >= NAME_MAX) {
		return -1;
	}
	// Make sure it doesn't contain any invalid characters
	if (strpbrk (name, ILLEGAL_LFN_CHARACTERS) != NULL) {
		return -1;
	}
	// Make sure the name doesn't contain any control codes or codes not representable in UCS-2
	for (i = 0; i < nameLength; i++) {
		unsigned char ch = (unsigned char) name[i];
		if (ch < 0x20 || ch >= ABOVE_UCS_RANGE) {
			return -1;
		}
	}
	// Convert to UCS-2 and get the resulting length
	ucsLength = mbsrtowcs(NULL, &tempName, MAX_LFN_LENGTH, NULL);
	if (ucsLength < 0 || ucsLength >= MAX_LFN_LENGTH) {
		return -1;
	}

	// Otherwise it is valid
	return ucsLength;
}