#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Curl_handler {int dummy; } ;
typedef  int /*<<< orphan*/  schemebuf ;
struct TYPE_6__ {char* scratch; char* scheme; char* temppath; char* fragment; char* query; char* path; char* host; } ;
typedef  scalar_t__ CURLUcode ;
typedef  TYPE_1__ CURLU ;

/* Variables and functions */
 scalar_t__ CURLUE_MALFORMED_INPUT ; 
 scalar_t__ CURLUE_OK ; 
 scalar_t__ CURLUE_OUT_OF_MEMORY ; 
 scalar_t__ CURLUE_UNSUPPORTED_SCHEME ; 
 unsigned int CURLU_DEFAULT_SCHEME ; 
 unsigned int CURLU_GUESS_SCHEME ; 
 unsigned int CURLU_NON_SUPPORT_SCHEME ; 
 unsigned int CURLU_NO_AUTHORITY ; 
 unsigned int CURLU_PATH_AS_IS ; 
 unsigned int CURLU_URLENCODE ; 
 size_t CURL_MAX_INPUT_LENGTH ; 
 struct Curl_handler* Curl_builtin_scheme (char*) ; 
 char* Curl_dedotdotify (char*) ; 
 scalar_t__ Curl_is_absolute_url (char const*,char*,int) ; 
 scalar_t__ Curl_parse_port (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 scalar_t__ DEFAULT_SCHEME ; 
 int FALSE ; 
 int /*<<< orphan*/  HOSTNAME_END (char const) ; 
 int /*<<< orphan*/  MAX_SCHEME_LEN ; 
 scalar_t__ STARTS_WITH_URL_DRIVE_PREFIX (char*) ; 
 int TRUE ; 
 scalar_t__ checkprefix (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hostname_check (TYPE_1__*,char*) ; 
 scalar_t__ junkscan (char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ parse_hostname_login (TYPE_1__*,struct Curl_handler const*,char**,unsigned int) ; 
 scalar_t__ strcasecompare (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strcpy_url (char*,char*,int) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static CURLUcode seturl(const char *url, CURLU *u, unsigned int flags)
{
  char *path;
  bool path_alloced = FALSE;
  char *hostname;
  char *query = NULL;
  char *fragment = NULL;
  CURLUcode result;
  bool url_has_scheme = FALSE;
  char schemebuf[MAX_SCHEME_LEN + 1];
  char *schemep = NULL;
  size_t schemelen = 0;
  size_t urllen;
  const struct Curl_handler *h = NULL;

  if(!url)
    return CURLUE_MALFORMED_INPUT;

  /*************************************************************
   * Parse the URL.
   ************************************************************/
  /* allocate scratch area */
  urllen = strlen(url);
  if(urllen > CURL_MAX_INPUT_LENGTH)
    /* excessive input length */
    return CURLUE_MALFORMED_INPUT;

  path = u->scratch = malloc(urllen * 2 + 2);
  if(!path)
    return CURLUE_OUT_OF_MEMORY;

  hostname = &path[urllen + 1];
  hostname[0] = 0;

  if(Curl_is_absolute_url(url, schemebuf, sizeof(schemebuf))) {
    url_has_scheme = TRUE;
    schemelen = strlen(schemebuf);
  }

  /* handle the file: scheme */
  if(url_has_scheme && strcasecompare(schemebuf, "file")) {
    /* path has been allocated large enough to hold this */
    strcpy(path, &url[5]);

    hostname = NULL; /* no host for file: URLs */
    u->scheme = strdup("file");
    if(!u->scheme)
      return CURLUE_OUT_OF_MEMORY;

    /* Extra handling URLs with an authority component (i.e. that start with
     * "file://")
     *
     * We allow omitted hostname (e.g. file:/<path>) -- valid according to
     * RFC 8089, but not the (current) WHAT-WG URL spec.
     */
    if(path[0] == '/' && path[1] == '/') {
      /* swallow the two slashes */
      char *ptr = &path[2];

      /*
       * According to RFC 8089, a file: URL can be reliably dereferenced if:
       *
       *  o it has no/blank hostname, or
       *
       *  o the hostname matches "localhost" (case-insensitively), or
       *
       *  o the hostname is a FQDN that resolves to this machine.
       *
       * For brevity, we only consider URLs with empty, "localhost", or
       * "127.0.0.1" hostnames as local.
       *
       * Additionally, there is an exception for URLs with a Windows drive
       * letter in the authority (which was accidentally omitted from RFC 8089
       * Appendix E, but believe me, it was meant to be there. --MK)
       */
      if(ptr[0] != '/' && !STARTS_WITH_URL_DRIVE_PREFIX(ptr)) {
        /* the URL includes a host name, it must match "localhost" or
           "127.0.0.1" to be valid */
        if(!checkprefix("localhost/", ptr) &&
           !checkprefix("127.0.0.1/", ptr)) {
          /* Invalid file://hostname/, expected localhost or 127.0.0.1 or
             none */
          return CURLUE_MALFORMED_INPUT;
        }
        ptr += 9; /* now points to the slash after the host */
      }

      path = ptr;
    }

#if !defined(MSDOS) && !defined(WIN32) && !defined(__CYGWIN__)
    /* Don't allow Windows drive letters when not in Windows.
     * This catches both "file:/c:" and "file:c:" */
    if(('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) ||
       STARTS_WITH_URL_DRIVE_PREFIX(path)) {
      /* File drive letters are only accepted in MSDOS/Windows */
      return CURLUE_MALFORMED_INPUT;
    }
#else
    /* If the path starts with a slash and a drive letter, ditch the slash */
    if('/' == path[0] && STARTS_WITH_URL_DRIVE_PREFIX(&path[1])) {
      /* This cannot be done with strcpy, as the memory chunks overlap! */
      memmove(path, &path[1], strlen(&path[1]) + 1);
    }
#endif

  }
  else {
    /* clear path */
    const char *p;
    const char *hostp;
    size_t len;
    path[0] = 0;

    if(url_has_scheme) {
      int i = 0;
      p = &url[schemelen + 1];
      while(p && (*p == '/') && (i < 4)) {
        p++;
        i++;
      }
      if((i < 1) || (i>3))
        /* less than one or more than three slashes */
        return CURLUE_MALFORMED_INPUT;

      schemep = schemebuf;
      if(!Curl_builtin_scheme(schemep) &&
         !(flags & CURLU_NON_SUPPORT_SCHEME))
        return CURLUE_UNSUPPORTED_SCHEME;

      if(junkscan(schemep))
        return CURLUE_MALFORMED_INPUT;

    }
    else {
      /* no scheme! */

      if(!(flags & (CURLU_DEFAULT_SCHEME|CURLU_GUESS_SCHEME)))
        return CURLUE_MALFORMED_INPUT;
      if(flags & CURLU_DEFAULT_SCHEME)
        schemep = (char *) DEFAULT_SCHEME;

      /*
       * The URL was badly formatted, let's try without scheme specified.
       */
      p = url;
    }
    hostp = p; /* host name starts here */

    while(*p && !HOSTNAME_END(*p)) /* find end of host name */
      p++;

    len = p - hostp;
    if(len) {
      memcpy(hostname, hostp, len);
      hostname[len] = 0;
    }
    else {
      if(!(flags & CURLU_NO_AUTHORITY))
        return CURLUE_MALFORMED_INPUT;
    }

    if((flags & CURLU_GUESS_SCHEME) && !schemep) {
      /* legacy curl-style guess based on host name */
      if(checkprefix("ftp.", hostname))
        schemep = (char *)"ftp";
      else if(checkprefix("dict.", hostname))
        schemep = (char *)"dict";
      else if(checkprefix("ldap.", hostname))
        schemep = (char *)"ldap";
      else if(checkprefix("imap.", hostname))
        schemep = (char *)"imap";
      else if(checkprefix("smtp.", hostname))
        schemep = (char *)"smtp";
      else if(checkprefix("pop3.", hostname))
        schemep = (char *)"pop3";
      else
        schemep = (char *)"http";
    }

    len = strlen(p);
    memcpy(path, p, len);
    path[len] = 0;

    u->scheme = strdup(schemep);
    if(!u->scheme)
      return CURLUE_OUT_OF_MEMORY;
  }

  /* if this is a known scheme, get some details */
  h = Curl_builtin_scheme(u->scheme);

  if(junkscan(path))
    return CURLUE_MALFORMED_INPUT;

  if((flags & CURLU_URLENCODE) && path[0]) {
    /* worst case output length is 3x the original! */
    char *newp = malloc(strlen(path) * 3);
    if(!newp)
      return CURLUE_OUT_OF_MEMORY;
    path_alloced = TRUE;
    strcpy_url(newp, path, TRUE); /* consider it relative */
    u->temppath = path = newp;
  }

  fragment = strchr(path, '#');
  if(fragment) {
    *fragment++ = 0;
    if(fragment[0]) {
      u->fragment = strdup(fragment);
      if(!u->fragment)
        return CURLUE_OUT_OF_MEMORY;
    }
  }

  query = strchr(path, '?');
  if(query) {
    *query++ = 0;
    /* done even if the query part is a blank string */
    u->query = strdup(query);
    if(!u->query)
      return CURLUE_OUT_OF_MEMORY;
  }

  if(!path[0])
    /* if there's no path left set, unset */
    path = NULL;
  else {
    if(!(flags & CURLU_PATH_AS_IS)) {
      /* remove ../ and ./ sequences according to RFC3986 */
      char *newp = Curl_dedotdotify(path);
      if(!newp)
        return CURLUE_OUT_OF_MEMORY;

      if(strcmp(newp, path)) {
        /* if we got a new version */
        if(path_alloced)
          Curl_safefree(u->temppath);
        u->temppath = path = newp;
        path_alloced = TRUE;
      }
      else
        free(newp);
    }

    u->path = path_alloced?path:strdup(path);
    if(!u->path)
      return CURLUE_OUT_OF_MEMORY;
    u->temppath = NULL; /* used now */
  }

  if(hostname) {
    /*
     * Parse the login details and strip them out of the host name.
     */
    if(junkscan(hostname))
      return CURLUE_MALFORMED_INPUT;

    result = parse_hostname_login(u, h, &hostname, flags);
    if(result)
      return result;

    result = Curl_parse_port(u, hostname);
    if(result)
      return result;

    if(0 == strlen(hostname) && (flags & CURLU_NO_AUTHORITY)) {
      /* Skip hostname check, it's allowed to be empty. */
    }
    else {
      result = hostname_check(u, hostname);
      if(result)
        return result;
    }

    u->host = strdup(hostname);
    if(!u->host)
      return CURLUE_OUT_OF_MEMORY;
  }

  Curl_safefree(u->scratch);
  Curl_safefree(u->temppath);

  return CURLUE_OK;
}