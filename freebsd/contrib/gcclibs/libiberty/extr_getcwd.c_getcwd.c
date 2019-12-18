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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  errno ; 
 char* getwd (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

char *
getcwd (char *buf, size_t len)
{
  char ourbuf[MAXPATHLEN];
  char *result;

  result = getwd (ourbuf);
  if (result) {
    if (strlen (ourbuf) >= len) {
      errno = ERANGE;
      return 0;
    }
    if (!buf) {
       buf = (char*)malloc(len);
       if (!buf) {
           errno = ENOMEM;
	   return 0;
       }
    }
    strcpy (buf, ourbuf);
  }
  return buf;
}