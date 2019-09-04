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
struct stat {scalar_t__ st_size; } ;
typedef  char* curl_off_t ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLAUTH_ANY ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_HTTPAUTH ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE_LARGE ; 
 int /*<<< orphan*/  CURLOPT_IOCTLDATA ; 
 int /*<<< orphan*/  CURLOPT_IOCTLFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_READDATA ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_USERPWD ; 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* curl_easy_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 char* my_ioctl ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* read_callback ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;
  int hd;
  struct stat file_info;

  char *file;
  char *url;

  if(argc < 3)
    return 1;

  file = argv[1];
  url = argv[2];

  /* get the file size of the local file */
  hd = open(file, O_RDONLY);
  fstat(hd, &file_info);

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* we want to use our own read function */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

    /* which file to upload */
    curl_easy_setopt(curl, CURLOPT_READDATA, (void *)&hd);

    /* set the ioctl function */
    curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, my_ioctl);

    /* pass the file descriptor to the ioctl callback as well */
    curl_easy_setopt(curl, CURLOPT_IOCTLDATA, (void *)&hd);

    /* enable "uploading" (which means PUT when doing HTTP) */
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /* specify target URL, and note that this URL should also include a file
       name, not only a directory (as you can do with GTP uploads) */
    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* and give the size of the upload, this supports large file sizes
       on systems that have general support for it */
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                     (curl_off_t)file_info.st_size);

    /* tell libcurl we can use "any" auth, which lets the lib pick one, but it
       also costs one extra round-trip and possibly sending of all the PUT
       data twice!!! */
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);

    /* set user name and password for the authentication */
    curl_easy_setopt(curl, CURLOPT_USERPWD, "user:password");

    /* Now run off and do what you've been told! */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  close(hd); /* close the local file */

  curl_global_cleanup();
  return 0;
}