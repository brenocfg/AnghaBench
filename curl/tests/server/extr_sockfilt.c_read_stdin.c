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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fullread (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  logmsg (char*) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static bool read_stdin(void *buffer, size_t nbytes)
{
  ssize_t nread = fullread(fileno(stdin), buffer, nbytes);
  if(nread != (ssize_t)nbytes) {
    logmsg("exiting...");
    return FALSE;
  }
  return TRUE;
}