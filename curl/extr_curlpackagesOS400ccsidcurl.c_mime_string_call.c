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
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  ASCII_CCSID ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 char* dynconvert (int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static CURLcode
mime_string_call(curl_mimepart *part, const char *string, unsigned int ccsid,
                 CURLcode (*mimefunc)(curl_mimepart *part, const char *string))

{
  char *s = (char *) NULL;
  CURLcode result;

  if(!string)
    return mimefunc(part, string);
  s = dynconvert(ASCII_CCSID, string, -1, ccsid);
  if(!s)
    return CURLE_OUT_OF_MEMORY;

  result = mimefunc(part, s);
  free(s);
  return result;
}