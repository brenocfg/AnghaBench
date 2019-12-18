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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_RTSP_REQUEST ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 scalar_t__ CURL_RTSPREQ_DESCRIBE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  my_curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void rtsp_describe(CURL *curl, const char *uri,
                          const char *sdp_filename)
{
  CURLcode res = CURLE_OK;
  FILE *sdp_fp = fopen(sdp_filename, "wb");
  printf("\nRTSP: DESCRIBE %s\n", uri);
  if(sdp_fp == NULL) {
    fprintf(stderr, "Could not open '%s' for writing\n", sdp_filename);
    sdp_fp = stdout;
  }
  else {
    printf("Writing SDP to '%s'\n", sdp_filename);
  }
  my_curl_easy_setopt(curl, CURLOPT_WRITEDATA, sdp_fp);
  my_curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, (long)CURL_RTSPREQ_DESCRIBE);
  my_curl_easy_perform(curl);
  my_curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
  if(sdp_fp != stdout) {
    fclose(sdp_fp);
  }
}