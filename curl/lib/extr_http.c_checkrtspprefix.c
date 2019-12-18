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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  statusline ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_convert_from_network (struct Curl_easy*,char*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STATUS_BAD ; 
 int /*<<< orphan*/  STATUS_DONE ; 
 int /*<<< orphan*/  STATUS_UNKNOWN ; 
 scalar_t__ checkprefixmax (char*,char const*,size_t) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static statusline
checkrtspprefix(struct Curl_easy *data,
                const char *s, size_t len)
{
  statusline result = STATUS_BAD;
  statusline onmatch = len >= 5? STATUS_DONE : STATUS_UNKNOWN;

#ifdef CURL_DOES_CONVERSIONS
  /* convert from the network encoding using a scratch area */
  char *scratch = strdup(s);
  if(NULL == scratch) {
    failf(data, "Failed to allocate memory for conversion!");
    return FALSE; /* can't return CURLE_OUT_OF_MEMORY so return FALSE */
  }
  if(CURLE_OK != Curl_convert_from_network(data, scratch, strlen(s) + 1)) {
    /* Curl_convert_from_network calls failf if unsuccessful */
    result = FALSE; /* can't return CURLE_foobar so return FALSE */
  }
  else if(checkprefixmax("RTSP/", scratch, len))
    result = onmatch;
  free(scratch);
#else
  (void)data; /* unused */
  if(checkprefixmax("RTSP/", s, len))
    result = onmatch;
#endif /* CURL_DOES_CONVERSIONS */

  return result;
}