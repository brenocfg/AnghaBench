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
struct stat {long st_size; } ;
struct input {int num; void* in; int /*<<< orphan*/ * hnd; } ;
typedef  long curl_off_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_DEBUGDATA ; 
 int /*<<< orphan*/  CURLOPT_DEBUGFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_HTTP_VERSION ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_PIPEWAIT ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYHOST ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYPEER ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 long CURL_HTTP_VERSION_2_0 ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 void* fopen (char const*,char*) ; 
 long my_trace ; 
 long read_callback ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 

__attribute__((used)) static void setup(struct input *i, int num, const char *upload)
{
  FILE *out;
  char url[256];
  char filename[128];
  struct stat file_info;
  curl_off_t uploadsize;
  CURL *hnd;

  hnd = i->hnd = curl_easy_init();
  i->num = num;
  snprintf(filename, 128, "dl-%d", num);
  out = fopen(filename, "wb");

  snprintf(url, 256, "https://localhost:8443/upload-%d", num);

  /* get the file size of the local file */
  stat(upload, &file_info);
  uploadsize = file_info.st_size;

  i->in = fopen(upload, "rb");

  /* write to this file */
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, out);

  /* we want to use our own read function */
  curl_easy_setopt(hnd, CURLOPT_READFUNCTION, read_callback);
  /* read from this file */
  curl_easy_setopt(hnd, CURLOPT_READDATA, i);
  /* provide the size of the upload */
  curl_easy_setopt(hnd, CURLOPT_INFILESIZE_LARGE, uploadsize);

  /* send in the URL to store the upload as */
  curl_easy_setopt(hnd, CURLOPT_URL, url);

  /* upload please */
  curl_easy_setopt(hnd, CURLOPT_UPLOAD, 1L);

  /* please be verbose */
  curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(hnd, CURLOPT_DEBUGFUNCTION, my_trace);
  curl_easy_setopt(hnd, CURLOPT_DEBUGDATA, i);

  /* HTTP/2 please */
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);

  /* we use a self-signed test server, skip verification during debugging */
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYHOST, 0L);

#if (CURLPIPE_MULTIPLEX > 0)
  /* wait for pipe connection to confirm */
  curl_easy_setopt(hnd, CURLOPT_PIPEWAIT, 1L);
#endif
}