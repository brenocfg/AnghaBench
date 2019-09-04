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
typedef  int /*<<< orphan*/  GETHOSTNAME_TYPE_ARG2 ;

/* Variables and functions */

int Curl_gethostname(char *name, GETHOSTNAME_TYPE_ARG2 namelen)
{
#ifndef HAVE_GETHOSTNAME

  /* Allow compilation and return failure when unavailable */
  (void) name;
  (void) namelen;
  return -1;

#else
  int err;
  char *dot;

#ifdef DEBUGBUILD

  /* Override host name when environment variable CURL_GETHOSTNAME is set */
  const char *force_hostname = getenv("CURL_GETHOSTNAME");
  if(force_hostname) {
    strncpy(name, force_hostname, namelen);
    err = 0;
  }
  else {
    name[0] = '\0';
    err = gethostname(name, namelen);
  }

#else /* DEBUGBUILD */

  /* The call to system's gethostname() might get intercepted by the
     libhostname library when libcurl is built as a non-debug shared
     library when running the test suite. */
  name[0] = '\0';
  err = gethostname(name, namelen);

#endif

  name[namelen - 1] = '\0';

  if(err)
    return err;

  /* Truncate domain, leave only machine name */
  dot = strchr(name, '.');
  if(dot)
    *dot = '\0';

  return 0;
#endif

}