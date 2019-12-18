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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XA_STRING ; 
 int /*<<< orphan*/  XA_WM_CLIENT_MACHINE ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SC_HOST_NAME_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int gethostname (char*,long) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ malloc (long) ; 
 int strlen (char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x11_set_window_pid(Display *dpy, Window win)
{
    long scret     = 0;
    char *hostname = NULL;
    pid_t pid      = getpid();

    XChangeProperty(dpy, win, XInternAtom(dpy, "_NET_WM_PID", False),
        XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&pid, 1);

    errno = 0;
    if ((scret = sysconf(_SC_HOST_NAME_MAX)) == -1 && errno)
        return;
    if ((hostname = (char*)malloc(scret + 1)) == NULL)
        return;

    if (gethostname(hostname, scret + 1) == -1)
        RARCH_WARN("Failed to get hostname.\n");
    else
    {
        XChangeProperty(dpy, win, XA_WM_CLIENT_MACHINE, XA_STRING, 8,
            PropModeReplace, (unsigned char *)hostname, strlen(hostname));
    }
    free(hostname);
}