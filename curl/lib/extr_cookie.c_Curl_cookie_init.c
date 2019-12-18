#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* cookie_engine; } ;
struct Curl_easy {TYPE_1__ state; } ;
struct CookieInfo {int newsession; void* running; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_cookie_add (struct Curl_easy*,struct CookieInfo*,int,void*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  Curl_cookie_cleanup (struct CookieInfo*) ; 
 scalar_t__ Curl_get_line (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FOPEN_READTEXT ; 
 scalar_t__ ISBLANK (char) ; 
 int /*<<< orphan*/  MAX_COOKIE_LINE ; 
 void* TRUE ; 
 struct CookieInfo* calloc (int,int) ; 
 scalar_t__ checkprefix (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_expired (struct CookieInfo*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct CookieInfo *Curl_cookie_init(struct Curl_easy *data,
                                    const char *file,
                                    struct CookieInfo *inc,
                                    bool newsession)
{
  struct CookieInfo *c;
  FILE *fp = NULL;
  bool fromfile = TRUE;
  char *line = NULL;

  if(NULL == inc) {
    /* we didn't get a struct, create one */
    c = calloc(1, sizeof(struct CookieInfo));
    if(!c)
      return NULL; /* failed to get memory */
    c->filename = strdup(file?file:"none"); /* copy the name just in case */
    if(!c->filename)
      goto fail; /* failed to get memory */
  }
  else {
    /* we got an already existing one, use that */
    c = inc;
  }
  c->running = FALSE; /* this is not running, this is init */

  if(file && !strcmp(file, "-")) {
    fp = stdin;
    fromfile = FALSE;
  }
  else if(file && !*file) {
    /* points to a "" string */
    fp = NULL;
  }
  else
    fp = file?fopen(file, FOPEN_READTEXT):NULL;

  c->newsession = newsession; /* new session? */

  if(fp) {
    char *lineptr;
    bool headerline;

    line = malloc(MAX_COOKIE_LINE);
    if(!line)
      goto fail;
    while(Curl_get_line(line, MAX_COOKIE_LINE, fp)) {
      if(checkprefix("Set-Cookie:", line)) {
        /* This is a cookie line, get it! */
        lineptr = &line[11];
        headerline = TRUE;
      }
      else {
        lineptr = line;
        headerline = FALSE;
      }
      while(*lineptr && ISBLANK(*lineptr))
        lineptr++;

      Curl_cookie_add(data, c, headerline, TRUE, lineptr, NULL, NULL, TRUE);
    }
    free(line); /* free the line buffer */
    remove_expired(c); /* run this once, not on every cookie */

    if(fromfile)
      fclose(fp);
  }

  c->running = TRUE;          /* now, we're running */
  if(data)
    data->state.cookie_engine = TRUE;

  return c;

fail:
  free(line);
  if(!inc)
    /* Only clean up if we allocated it here, as the original could still be in
     * use by a share handle */
    Curl_cookie_cleanup(c);
  if(fromfile && fp)
    fclose(fp);
  return NULL; /* out of memory */
}