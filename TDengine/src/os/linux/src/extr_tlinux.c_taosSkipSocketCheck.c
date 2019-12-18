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
struct utsname {int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int /*<<< orphan*/  pPrint (char*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uname (struct utsname*) ; 

bool taosSkipSocketCheck() {
  struct utsname buf;
  if (uname(&buf)) {
    pPrint("can't fetch os info");
    return false;
  }

  if (strstr(buf.release, "Microsoft") != 0) {
    pPrint("using WSLv1");
    return true;
  }

  return false;
}