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
 char* Curl_thread_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LK_CURL_VERSION ; 
 int MAX_CONV_EXPANSION ; 
 scalar_t__ convert (char*,int,unsigned int,char*,int,int /*<<< orphan*/ ) ; 
 char* curl_version () ; 
 int strlen (char*) ; 

char *
curl_version_ccsid(unsigned int ccsid)

{
  int i;
  char *aversion;
  char *eversion;

  aversion = curl_version();

  if(!aversion)
    return aversion;

  i = strlen(aversion) + 1;
  i *= MAX_CONV_EXPANSION;

  eversion = Curl_thread_buffer(LK_CURL_VERSION, i);
  if(!eversion)
    return (char *) NULL;

  if(convert(eversion, i, ccsid, aversion, -1, ASCII_CCSID) < 0)
    return (char *) NULL;

  return eversion;
}