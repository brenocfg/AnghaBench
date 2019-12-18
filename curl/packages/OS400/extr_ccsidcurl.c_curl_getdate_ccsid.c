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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASCII_CCSID ; 
 int /*<<< orphan*/  curl_getdate (char const*,int /*<<< orphan*/  const*) ; 
 char* dynconvert (int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 

time_t
curl_getdate_ccsid(const char *p, const time_t * unused, unsigned int ccsid)

{
  char *s;
  time_t t;

  if(!p)
    return curl_getdate(p, unused);

  s = dynconvert(ASCII_CCSID, p, -1, ccsid);

  if(!s)
    return (time_t) -1;

  t = curl_getdate(s, unused);
  free(s);
  return t;
}