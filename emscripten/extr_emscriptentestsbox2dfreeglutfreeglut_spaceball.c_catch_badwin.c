#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ error_code; } ;
typedef  TYPE_1__ XErrorEvent ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 scalar_t__ BadWindow ; 
 int /*<<< orphan*/  XGetErrorText (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int catch_badwin(Display *dpy, XErrorEvent *err)
{
  char buf[256];

  if(err->error_code == BadWindow) {
    /* do nothing? */
  } else {
    XGetErrorText(dpy, err->error_code, buf, sizeof buf);
    fprintf(stderr, "Caught unexpected X error: %s\n", buf);
  }
  return 0;
}