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
typedef  char FILE ;
typedef  int CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_NOBODY ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int HTTP_COMMAND_HEAD ; 
 int curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fclose (char*) ; 
 char* fopen (char*,char*) ; 

int SyncTime_CURL_Fetch(CURL *curl, char *URL_Str, char *OutFileName,
                        int HttpGetBody)
{
  FILE *outfile;
  CURLcode res;

  outfile = NULL;
  if(HttpGetBody == HTTP_COMMAND_HEAD)
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
  else {
    outfile = fopen(OutFileName, "wb");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
  }

  curl_easy_setopt(curl, CURLOPT_URL, URL_Str);
  res = curl_easy_perform(curl);
  if(outfile != NULL)
    fclose(outfile);
  return res;  /* (CURLE_OK) */
}