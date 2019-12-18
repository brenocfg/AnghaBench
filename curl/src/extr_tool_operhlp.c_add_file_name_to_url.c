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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 char* aprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 char* curl_easy_escape (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 void* strrchr (char const*,char) ; 
 char* strstr (char*,char*) ; 

char *add_file_name_to_url(char *url, const char *filename)
{
  /* If no file name part is given in the URL, we add this file name */
  char *ptr = strstr(url, "://");
  CURL *curl = curl_easy_init(); /* for url escaping */
  if(!curl)
    return NULL; /* error! */
  if(ptr)
    ptr += 3;
  else
    ptr = url;
  ptr = strrchr(ptr, '/');
  if(!ptr || !strlen(++ptr)) {
    /* The URL has no file name part, add the local file name. In order
       to be able to do so, we have to create a new URL in another
       buffer.*/

    /* We only want the part of the local path that is on the right
       side of the rightmost slash and backslash. */
    const char *filep = strrchr(filename, '/');
    char *file2 = strrchr(filep?filep:filename, '\\');
    char *encfile;

    if(file2)
      filep = file2 + 1;
    else if(filep)
      filep++;
    else
      filep = filename;

    /* URL encode the file name */
    encfile = curl_easy_escape(curl, filep, 0 /* use strlen */);
    if(encfile) {
      char *urlbuffer;
      if(ptr)
        /* there is a trailing slash on the URL */
        urlbuffer = aprintf("%s%s", url, encfile);
      else
        /* there is no trailing slash on the URL */
        urlbuffer = aprintf("%s/%s", url, encfile);

      curl_free(encfile);
      Curl_safefree(url);

      if(!urlbuffer)
        return NULL;

      url = urlbuffer; /* use our new URL instead! */
    }
    else
      Curl_safefree(url);
  }
  curl_easy_cleanup(curl);
  return url;
}