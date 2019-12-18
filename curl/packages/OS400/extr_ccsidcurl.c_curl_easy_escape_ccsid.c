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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 unsigned int ASCII_CCSID ; 
 int /*<<< orphan*/  EINVAL ; 
 char* curl_easy_escape (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* dynconvert (unsigned int,char const*,int,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 

char *
curl_easy_escape_ccsid(CURL *handle, const char *string, int length,
                       unsigned int sccsid, unsigned int dccsid)

{
  char *s;
  char *d;

  if(!string) {
    errno = EINVAL;
    return (char *) NULL;
    }

  s = dynconvert(ASCII_CCSID, string, length? length: -1, sccsid);

  if(!s)
    return (char *) NULL;

  d = curl_easy_escape(handle, s, 0);
  free(s);

  if(!d)
    return (char *) NULL;

  s = dynconvert(dccsid, d, -1, ASCII_CCSID);
  free(d);
  return s;
}