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
typedef  scalar_t__ ALenum ;

/* Variables and functions */
 scalar_t__ ALUT_ERROR_NO_ERROR ; 
 char* alutGetErrorString (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getenv (char*) ; 
 scalar_t__ lastError ; 
 int /*<<< orphan*/  stderr ; 

void _alutSetError(ALenum err)
{
  /* print a message to stderr if ALUT_DEBUG environment variable is defined */
  if (getenv("ALUT_DEBUG"))
  {
    fprintf(stderr, "ALUT error: %s\n", alutGetErrorString(err));
  }

  if (lastError == ALUT_ERROR_NO_ERROR)
  {
    lastError = err;
  }
}