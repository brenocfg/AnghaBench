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
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  ASCII_CCSID ; 
 char* Curl_thread_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LK_MULTI_STRERROR ; 
 int MAX_CONV_EXPANSION ; 
 scalar_t__ convert (char*,int,unsigned int,char const*,int,int /*<<< orphan*/ ) ; 
 char* curl_multi_strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

const char *
curl_multi_strerror_ccsid(CURLMcode error, unsigned int ccsid)

{
  int i;
  const char *s;
  char *buf;

  s = curl_multi_strerror(error);

  if(!s)
    return s;

  i = MAX_CONV_EXPANSION * (strlen(s) + 1);

  buf = Curl_thread_buffer(LK_MULTI_STRERROR, i);
  if(!buf)
    return (const char *) NULL;

  if(convert(buf, i, ccsid, s, -1, ASCII_CCSID) < 0)
    return (const char *) NULL;

  return (const char *) buf;
}