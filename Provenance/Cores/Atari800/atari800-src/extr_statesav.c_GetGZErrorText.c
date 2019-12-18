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
 char* GZERROR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  StateFile ; 
 scalar_t__ Z_ERRNO ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ nFileError ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void GetGZErrorText(void)
{
#ifdef GZERROR
	const char *error = GZERROR(StateFile, &nFileError);
	if (nFileError == Z_ERRNO) {
#ifdef HAVE_STRERROR
		Log_print("The following general file I/O error occurred:");
		Log_print(strerror(errno));
#else
		Log_print("A file I/O error occurred");
#endif
		return;
	}
	Log_print("ZLIB returned the following error: %s", error);
#endif /* GZERROR */
	Log_print("State file I/O failed.");
}