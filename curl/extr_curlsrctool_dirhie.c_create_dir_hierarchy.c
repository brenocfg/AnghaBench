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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_WRITE_ERROR ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  DIR_CHAR ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  PATH_DELIMITERS ; 
 scalar_t__ errno ; 
 char* malloc (size_t) ; 
 int mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_dir_errno (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

CURLcode create_dir_hierarchy(const char *outfile, FILE *errors)
{
  char *tempdir;
  char *tempdir2;
  char *outdup;
  char *dirbuildup;
  CURLcode result = CURLE_OK;
  size_t outlen;

  outlen = strlen(outfile);
  outdup = strdup(outfile);
  if(!outdup)
    return CURLE_OUT_OF_MEMORY;

  dirbuildup = malloc(outlen + 1);
  if(!dirbuildup) {
    Curl_safefree(outdup);
    return CURLE_OUT_OF_MEMORY;
  }
  dirbuildup[0] = '\0';

  /* Allow strtok() here since this isn't used threaded */
  /* !checksrc! disable BANNEDFUNC 2 */
  tempdir = strtok(outdup, PATH_DELIMITERS);

  while(tempdir != NULL) {
    tempdir2 = strtok(NULL, PATH_DELIMITERS);
    /* since strtok returns a token for the last word even
       if not ending with DIR_CHAR, we need to prune it */
    if(tempdir2 != NULL) {
      size_t dlen = strlen(dirbuildup);
      if(dlen)
        msnprintf(&dirbuildup[dlen], outlen - dlen, "%s%s", DIR_CHAR, tempdir);
      else {
        if(outdup == tempdir)
          /* the output string doesn't start with a separator */
          strcpy(dirbuildup, tempdir);
        else
          msnprintf(dirbuildup, outlen, "%s%s", DIR_CHAR, tempdir);
      }
      if((-1 == mkdir(dirbuildup, (mode_t)0000750)) && (errno != EEXIST)) {
        show_dir_errno(errors, dirbuildup);
        result = CURLE_WRITE_ERROR;
        break; /* get out of loop */
      }
    }
    tempdir = tempdir2;
  }

  Curl_safefree(dirbuildup);
  Curl_safefree(outdup);

  return result;
}