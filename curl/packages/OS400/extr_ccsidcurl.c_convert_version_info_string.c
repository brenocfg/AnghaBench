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
 int /*<<< orphan*/  ASCII_CCSID ; 
 int convert (char*,int,unsigned int,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
convert_version_info_string(const char * * stringp,
                            char * * bufp, int *left, unsigned int ccsid)

{
  /* Helper for curl_version_info_ccsid(): convert a string if defined.
     Result is stored in the `*left'-byte buffer at `*bufp'.
     `*bufp' and `*left' are updated accordingly.
     Return 0 if ok, else -1. */

  if(*stringp) {
    int l = convert(*bufp, *left, ccsid, *stringp, -1, ASCII_CCSID);

    if(l <= 0)
      return -1;

    *stringp = *bufp;
    *bufp += l;
    *left -= l;
    }

  return 0;
}