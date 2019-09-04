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
typedef  int /*<<< orphan*/  urlbuf ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FAILONERROR ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  curl_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * handles ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * urlstring ; 
 char* write_callback ; 

__attribute__((used)) static void setup_handle(char *base_url, CURLM *m, int handlenum)
{
  char urlbuf[256];

  msnprintf(urlbuf, sizeof(urlbuf), "%s%s", base_url, urlstring[handlenum]);
  curl_easy_setopt(handles[handlenum], CURLOPT_URL, urlbuf);
  curl_easy_setopt(handles[handlenum], CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(handles[handlenum], CURLOPT_FAILONERROR, 1L);
  curl_easy_setopt(handles[handlenum], CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(handles[handlenum], CURLOPT_WRITEDATA, NULL);
  curl_multi_add_handle(m, handles[handlenum]);
}