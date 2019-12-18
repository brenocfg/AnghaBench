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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ SANITIZEcode ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 char* curlx_getenv (char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ sanitize_file_name (char**,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 char* strrchr (char const*,char) ; 
 char* strstr (char const*,char*) ; 

CURLcode get_url_file_name(char **filename, const char *url)
{
  const char *pc, *pc2;

  *filename = NULL;

  /* Find and get the remote file name */
  pc = strstr(url, "://");
  if(pc)
    pc += 3;
  else
    pc = url;

  pc2 = strrchr(pc, '\\');
  pc = strrchr(pc, '/');
  if(pc2 && (!pc || pc < pc2))
    pc = pc2;

  if(pc)
    /* duplicate the string beyond the slash */
    pc++;
  else
    /* no slash => empty string */
    pc = "";

  *filename = strdup(pc);
  if(!*filename)
    return CURLE_OUT_OF_MEMORY;

#if defined(MSDOS) || defined(WIN32)
  {
    char *sanitized;
    SANITIZEcode sc = sanitize_file_name(&sanitized, *filename, 0);
    Curl_safefree(*filename);
    if(sc)
      return CURLE_URL_MALFORMAT;
    *filename = sanitized;
  }
#endif /* MSDOS || WIN32 */

  /* in case we built debug enabled, we allow an environment variable
   * named CURL_TESTDIR to prefix the given file name to put it into a
   * specific directory
   */
#ifdef DEBUGBUILD
  {
    char *tdir = curlx_getenv("CURL_TESTDIR");
    if(tdir) {
      char buffer[512]; /* suitably large */
      msnprintf(buffer, sizeof(buffer), "%s/%s", tdir, *filename);
      Curl_safefree(*filename);
      *filename = strdup(buffer); /* clone the buffer */
      curl_free(tdir);
      if(!*filename)
        return CURLE_OUT_OF_MEMORY;
    }
  }
#endif

  return CURLE_OK;
}