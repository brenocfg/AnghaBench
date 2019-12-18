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
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ passwd_fp ; 
 int /*<<< orphan*/  passwdfile ; 

__attribute__((used)) static void
hlfsd_endpwent(void)
{
  if (!passwdfile) {
    /*
     * Don't actually run this because we will be making more passwd calls
     * afterwards.  On Solaris 2.5.1, making getpwent() calls after calling
     * endpwent() results in a memory leak! (and no, even Purify didn't
     * detect it...)
     *
     endpwent();
     */
    return;
  }

  if (passwd_fp) {
    fclose(passwd_fp);
  }
}