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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static bool pathmatch(const char *cookie_path, const char *request_uri)
{
  size_t cookie_path_len;
  size_t uri_path_len;
  char *uri_path = NULL;
  char *pos;
  bool ret = FALSE;

  /* cookie_path must not have last '/' separator. ex: /sample */
  cookie_path_len = strlen(cookie_path);
  if(1 == cookie_path_len) {
    /* cookie_path must be '/' */
    return TRUE;
  }

  uri_path = strdup(request_uri);
  if(!uri_path)
    return FALSE;
  pos = strchr(uri_path, '?');
  if(pos)
    *pos = 0x0;

  /* #-fragments are already cut off! */
  if(0 == strlen(uri_path) || uri_path[0] != '/') {
    free(uri_path);
    uri_path = strdup("/");
    if(!uri_path)
      return FALSE;
  }

  /* here, RFC6265 5.1.4 says
     4. Output the characters of the uri-path from the first character up
        to, but not including, the right-most %x2F ("/").
     but URL path /hoge?fuga=xxx means /hoge/index.cgi?fuga=xxx in some site
     without redirect.
     Ignore this algorithm because /hoge is uri path for this case
     (uri path is not /).
   */

  uri_path_len = strlen(uri_path);

  if(uri_path_len < cookie_path_len) {
    ret = FALSE;
    goto pathmatched;
  }

  /* not using checkprefix() because matching should be case-sensitive */
  if(strncmp(cookie_path, uri_path, cookie_path_len)) {
    ret = FALSE;
    goto pathmatched;
  }

  /* The cookie-path and the uri-path are identical. */
  if(cookie_path_len == uri_path_len) {
    ret = TRUE;
    goto pathmatched;
  }

  /* here, cookie_path_len < uri_path_len */
  if(uri_path[cookie_path_len] == '/') {
    ret = TRUE;
    goto pathmatched;
  }

  ret = FALSE;

pathmatched:
  free(uri_path);
  return ret;
}