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
 scalar_t__ fullwrite (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  logmsg (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static bool write_stdout(const void *buffer, size_t nbytes)
{
  ssize_t nwrite = fullwrite(fileno(stdout), buffer, nbytes);
  if(nwrite != (ssize_t)nbytes) {
    logmsg("exiting...");
    return FALSE;
  }
  return TRUE;
}