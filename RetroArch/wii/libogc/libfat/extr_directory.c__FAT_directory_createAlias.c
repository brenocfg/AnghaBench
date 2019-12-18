#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  ps ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mbstate_t ;

/* Variables and functions */
 int EOF ; 
 char const* ILLEGAL_ALIAS_CHARACTERS ; 
 int MAX_ALIAS_EXT_LENGTH ; 
 scalar_t__ NAME_MAX ; 
 int mbrtowc (scalar_t__*,char const*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char const* strchr (char const*,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  towupper (int /*<<< orphan*/ ) ; 
 int wctob (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _FAT_directory_createAlias (char* alias, const char* lfn) {
	bool lossyConversion = false;	// Set when the alias had to be modified to be valid
	int lfnPos = 0;
	int aliasPos = 0;
	wchar_t lfnChar;
	int oemChar;
	mbstate_t ps = {0};
	int bytesUsed = 0;
	const char* lfnExt;
	int aliasExtLen;

	// Strip leading periods
	while (lfn[lfnPos] == '.') {
		lfnPos ++;
		lossyConversion = true;
	}

	// Primary portion of alias
	while (aliasPos < 8 && lfn[lfnPos] != '.' && lfn[lfnPos] != '\0') {
		bytesUsed = mbrtowc(&lfnChar, lfn + lfnPos, NAME_MAX - lfnPos, &ps);
		if (bytesUsed < 0) {
			return -1;
		}
		oemChar = wctob(towupper((wint_t)lfnChar));
		if (wctob((wint_t)lfnChar) != oemChar) {
			// Case of letter was changed
			lossyConversion = true;
		}
		if (oemChar == ' ') {
			// Skip spaces in filename
			lossyConversion = true;
			lfnPos += bytesUsed;
			continue;
		}
		if (oemChar == EOF) {
			oemChar = '_';		// Replace unconvertable characters with underscores
			lossyConversion = true;
		}
		if (strchr (ILLEGAL_ALIAS_CHARACTERS, oemChar) != NULL) {
			// Invalid Alias character
			oemChar = '_';		// Replace illegal characters with underscores
			lossyConversion = true;
		}

		alias[aliasPos] = (char)oemChar;
		aliasPos++;
		lfnPos += bytesUsed;
	}

	if (lfn[lfnPos] != '.' && lfn[lfnPos] != '\0') {
		// Name was more than 8 characters long
		lossyConversion = true;
	}

	// Alias extension
	lfnExt = strrchr (lfn, '.');
	if (lfnExt != NULL && lfnExt != strchr (lfn, '.')) {
		// More than one period in name
		lossyConversion = true;
	}
	if (lfnExt != NULL && lfnExt[1] != '\0') {
		lfnExt++;
		alias[aliasPos] = '.';
		aliasPos++;
		memset (&ps, 0, sizeof(ps));
		for (aliasExtLen = 0; aliasExtLen < MAX_ALIAS_EXT_LENGTH && *lfnExt != '\0'; aliasExtLen++) {
			bytesUsed = mbrtowc(&lfnChar, lfnExt, NAME_MAX - lfnPos, &ps);
			if (bytesUsed < 0) {
				return -1;
			}
			oemChar = wctob(towupper((wint_t)lfnChar));
			if (wctob((wint_t)lfnChar) != oemChar) {
				// Case of letter was changed
				lossyConversion = true;
			}
			if (oemChar == ' ') {
				// Skip spaces in alias
				lossyConversion = true;
				lfnExt += bytesUsed;
				continue;
			}
			if (oemChar == EOF) {
				oemChar = '_';		// Replace unconvertable characters with underscores
				lossyConversion = true;
			}
			if (strchr (ILLEGAL_ALIAS_CHARACTERS, oemChar) != NULL) {
				// Invalid Alias character
				oemChar = '_';		// Replace illegal characters with underscores
				lossyConversion = true;
			}

			alias[aliasPos] = (char)oemChar;
			aliasPos++;
			lfnExt += bytesUsed;
		}
		if (*lfnExt != '\0') {
			// Extension was more than 3 characters long
			lossyConversion = true;
		}
	}

	alias[aliasPos] = '\0';
	if (lossyConversion) {
		return aliasPos;
	} else {
		return 0;
	}
}