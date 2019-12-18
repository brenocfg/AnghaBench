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
 char* TTY_DEVICE ; 
 char* dlg_strclone (char const*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* ttyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
open_terminal(char **result, int mode)
{
    const char *device = TTY_DEVICE;
    if (!isatty(fileno(stderr))
	|| (device = ttyname(fileno(stderr))) == 0) {
	if (!isatty(fileno(stdout))
	    || (device = ttyname(fileno(stdout))) == 0) {
	    if (!isatty(fileno(stdin))
		|| (device = ttyname(fileno(stdin))) == 0) {
		device = TTY_DEVICE;
	    }
	}
    }
    *result = dlg_strclone(device);
    return open(device, mode);
}