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
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  PRINT_PERR (char*,char const*) ; 
 int /*<<< orphan*/  PRINT_TRACE (char*,char const*,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_to_file(const char *file, const char *command)
{
	int fh;

	PRINT_TRACE("Write: %s - %s\n", file, command);
	fh = open(file, O_WRONLY);
	if (fh == -1) {
		PRINT_PERR("Could not open %s\n", file);
		return -1;
	}
	if (write(fh, command, strlen(command)) == -1) {
		PRINT_PERR("Write to %s failed\n", file);
		close(fh);
		return -1;
	};
	close(fh);
	return 0;
}