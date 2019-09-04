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
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  passwd ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  curlx_msnprintf (char*,int,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  getpass_r (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static CURLcode checkpasswd(const char *kind, /* for what purpose */
                            const size_t i,   /* operation index */
                            const bool last,  /* TRUE if last operation */
                            char **userpwd)   /* pointer to allocated string */
{
  char *psep;
  char *osep;

  if(!*userpwd)
    return CURLE_OK;

  /* Attempt to find the password separator */
  psep = strchr(*userpwd, ':');

  /* Attempt to find the options separator */
  osep = strchr(*userpwd, ';');

  if(!psep && **userpwd != ';') {
    /* no password present, prompt for one */
    char passwd[256] = "";
    char prompt[256];
    size_t passwdlen;
    size_t userlen = strlen(*userpwd);
    char *passptr;

    if(osep)
      *osep = '\0';

    /* build a nice-looking prompt */
    if(!i && last)
      curlx_msnprintf(prompt, sizeof(prompt),
                      "Enter %s password for user '%s':",
                      kind, *userpwd);
    else
      curlx_msnprintf(prompt, sizeof(prompt),
                      "Enter %s password for user '%s' on URL #%zu:",
                      kind, *userpwd, i + 1);

    /* get password */
    getpass_r(prompt, passwd, sizeof(passwd));
    passwdlen = strlen(passwd);

    if(osep)
      *osep = ';';

    /* extend the allocated memory area to fit the password too */
    passptr = realloc(*userpwd,
                      passwdlen + 1 + /* an extra for the colon */
                      userlen + 1);   /* an extra for the zero */
    if(!passptr)
      return CURLE_OUT_OF_MEMORY;

    /* append the password separated with a colon */
    passptr[userlen] = ':';
    memcpy(&passptr[userlen + 1], passwd, passwdlen + 1);
    *userpwd = passptr;
  }

  return CURLE_OK;
}