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
typedef  int curl_off_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_GOT_NOTHING ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_APPEND ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _fseeki64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 long readfunc ; 
 int sftpGetRemoteFileSize (char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int sftpResumeUpload(CURL *curlhandle, const char *remotepath,
                            const char *localpath)
{
  FILE *f = NULL;
  CURLcode result = CURLE_GOT_NOTHING;

  curl_off_t remoteFileSizeByte = sftpGetRemoteFileSize(remotepath);
  if(-1 == remoteFileSizeByte) {
    printf("Error reading the remote file size: unable to resume upload\n");
    return -1;
  }

  f = fopen(localpath, "rb");
  if(!f) {
    perror(NULL);
    return 0;
  }

  curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);
  curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
  curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);

#ifdef _WIN32
  _fseeki64(f, remoteFileSizeByte, SEEK_SET);
#else
  fseek(f, (long)remoteFileSizeByte, SEEK_SET);
#endif
  curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
  result = curl_easy_perform(curlhandle);

  fclose(f);

  if(result == CURLE_OK)
    return 1;
  else {
    fprintf(stderr, "%s\n", curl_easy_strerror(result));
    return 0;
  }
}