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
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_GOT_NOTHING ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_APPEND ; 
 int /*<<< orphan*/  CURLOPT_FTPPORT ; 
 int /*<<< orphan*/  CURLOPT_FTP_CREATE_MISSING_DIRS ; 
 int /*<<< orphan*/  CURLOPT_FTP_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_HEADERFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_NOBODY ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 long discardfunc ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long getcontentlengthfunc ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ *) ; 
 long readfunc ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int upload(CURL *curlhandle, const char *remotepath,
                  const char *localpath, long timeout, long tries)
{
  FILE *f;
  long uploaded_len = 0;
  CURLcode r = CURLE_GOT_NOTHING;
  int c;

  f = fopen(localpath, "rb");
  if(!f) {
    perror(NULL);
    return 0;
  }

  curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);

  curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);

  if(timeout)
    curl_easy_setopt(curlhandle, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);

  curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
  curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &uploaded_len);

  curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardfunc);

  curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
  curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);

  /* disable passive mode */
  curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-");
  curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);

  curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);

  for(c = 0; (r != CURLE_OK) && (c < tries); c++) {
    /* are we resuming? */
    if(c) { /* yes */
      /* determine the length of the file already written */

      /*
       * With NOBODY and NOHEADER, libcurl will issue a SIZE
       * command, but the only way to retrieve the result is
       * to parse the returned Content-Length header. Thus,
       * getcontentlengthfunc(). We need discardfunc() above
       * because HEADER will dump the headers to stdout
       * without it.
       */
      curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
      curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);

      r = curl_easy_perform(curlhandle);
      if(r != CURLE_OK)
        continue;

      curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
      curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);

      fseek(f, uploaded_len, SEEK_SET);

      curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
    }
    else { /* no */
      curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);
    }

    r = curl_easy_perform(curlhandle);
  }

  fclose(f);

  if(r == CURLE_OK)
    return 1;
  else {
    fprintf(stderr, "%s\n", curl_easy_strerror(r));
    return 0;
  }
}