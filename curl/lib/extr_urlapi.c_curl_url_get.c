#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Curl_handler {char* defport; int flags; } ;
typedef  int /*<<< orphan*/  portbuf ;
struct TYPE_3__ {char* scheme; char* user; char* password; char* options; char* host; char* zoneid; char* port; char* portnum; char* path; char* query; char* fragment; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURLUcode ;
typedef  int CURLUPart ;
typedef  TYPE_1__ CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUE_BAD_HANDLE ; 
 int /*<<< orphan*/  CURLUE_BAD_PARTPOINTER ; 
 int /*<<< orphan*/  CURLUE_NO_FRAGMENT ; 
 int /*<<< orphan*/  CURLUE_NO_HOST ; 
 int /*<<< orphan*/  CURLUE_NO_OPTIONS ; 
 int /*<<< orphan*/  CURLUE_NO_PASSWORD ; 
 int /*<<< orphan*/  CURLUE_NO_PORT ; 
 int /*<<< orphan*/  CURLUE_NO_QUERY ; 
 int /*<<< orphan*/  CURLUE_NO_SCHEME ; 
 int /*<<< orphan*/  CURLUE_NO_USER ; 
 int /*<<< orphan*/  CURLUE_OK ; 
 int /*<<< orphan*/  CURLUE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLUE_UNKNOWN_PART ; 
 int /*<<< orphan*/  CURLUE_URLDECODE ; 
#define  CURLUPART_FRAGMENT 138 
#define  CURLUPART_HOST 137 
#define  CURLUPART_OPTIONS 136 
#define  CURLUPART_PASSWORD 135 
#define  CURLUPART_PATH 134 
#define  CURLUPART_PORT 133 
#define  CURLUPART_QUERY 132 
#define  CURLUPART_SCHEME 131 
#define  CURLUPART_URL 130 
#define  CURLUPART_USER 129 
#define  CURLUPART_ZONEID 128 
 unsigned int CURLU_DEFAULT_PORT ; 
 unsigned int CURLU_DEFAULT_SCHEME ; 
 unsigned int CURLU_NO_DEFAULT_PORT ; 
 unsigned int CURLU_URLDECODE ; 
 struct Curl_handler* Curl_builtin_scheme (char*) ; 
 scalar_t__ Curl_urldecode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEFAULT_SCHEME ; 
 int FALSE ; 
 int PROTOPT_URLOPTIONS ; 
 int /*<<< orphan*/  TRUE ; 
 char* aprintf (char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcasecompare (char*,char*) ; 
 void* strdup (char*) ; 
 size_t strlen (char*) ; 

CURLUcode curl_url_get(CURLU *u, CURLUPart what,
                       char **part, unsigned int flags)
{
  char *ptr;
  CURLUcode ifmissing = CURLUE_UNKNOWN_PART;
  char portbuf[7];
  bool urldecode = (flags & CURLU_URLDECODE)?1:0;
  bool plusdecode = FALSE;
  (void)flags;
  if(!u)
    return CURLUE_BAD_HANDLE;
  if(!part)
    return CURLUE_BAD_PARTPOINTER;
  *part = NULL;

  switch(what) {
  case CURLUPART_SCHEME:
    ptr = u->scheme;
    ifmissing = CURLUE_NO_SCHEME;
    urldecode = FALSE; /* never for schemes */
    break;
  case CURLUPART_USER:
    ptr = u->user;
    ifmissing = CURLUE_NO_USER;
    break;
  case CURLUPART_PASSWORD:
    ptr = u->password;
    ifmissing = CURLUE_NO_PASSWORD;
    break;
  case CURLUPART_OPTIONS:
    ptr = u->options;
    ifmissing = CURLUE_NO_OPTIONS;
    break;
  case CURLUPART_HOST:
    ptr = u->host;
    ifmissing = CURLUE_NO_HOST;
    break;
  case CURLUPART_ZONEID:
    ptr = u->zoneid;
    break;
  case CURLUPART_PORT:
    ptr = u->port;
    ifmissing = CURLUE_NO_PORT;
    urldecode = FALSE; /* never for port */
    if(!ptr && (flags & CURLU_DEFAULT_PORT) && u->scheme) {
      /* there's no stored port number, but asked to deliver
         a default one for the scheme */
      const struct Curl_handler *h =
        Curl_builtin_scheme(u->scheme);
      if(h) {
        msnprintf(portbuf, sizeof(portbuf), "%ld", h->defport);
        ptr = portbuf;
      }
    }
    else if(ptr && u->scheme) {
      /* there is a stored port number, but ask to inhibit if
         it matches the default one for the scheme */
      const struct Curl_handler *h =
        Curl_builtin_scheme(u->scheme);
      if(h && (h->defport == u->portnum) &&
         (flags & CURLU_NO_DEFAULT_PORT))
        ptr = NULL;
    }
    break;
  case CURLUPART_PATH:
    ptr = u->path;
    if(!ptr) {
      ptr = u->path = strdup("/");
      if(!u->path)
        return CURLUE_OUT_OF_MEMORY;
    }
    break;
  case CURLUPART_QUERY:
    ptr = u->query;
    ifmissing = CURLUE_NO_QUERY;
    plusdecode = urldecode;
    break;
  case CURLUPART_FRAGMENT:
    ptr = u->fragment;
    ifmissing = CURLUE_NO_FRAGMENT;
    break;
  case CURLUPART_URL: {
    char *url;
    char *scheme;
    char *options = u->options;
    char *port = u->port;
    char *allochost = NULL;
    if(u->scheme && strcasecompare("file", u->scheme)) {
      url = aprintf("file://%s%s%s",
                    u->path,
                    u->fragment? "#": "",
                    u->fragment? u->fragment : "");
    }
    else if(!u->host)
      return CURLUE_NO_HOST;
    else {
      const struct Curl_handler *h = NULL;
      if(u->scheme)
        scheme = u->scheme;
      else if(flags & CURLU_DEFAULT_SCHEME)
        scheme = (char *) DEFAULT_SCHEME;
      else
        return CURLUE_NO_SCHEME;

      h = Curl_builtin_scheme(scheme);
      if(!port && (flags & CURLU_DEFAULT_PORT)) {
        /* there's no stored port number, but asked to deliver
           a default one for the scheme */
        if(h) {
          msnprintf(portbuf, sizeof(portbuf), "%ld", h->defport);
          port = portbuf;
        }
      }
      else if(port) {
        /* there is a stored port number, but asked to inhibit if it matches
           the default one for the scheme */
        if(h && (h->defport == u->portnum) &&
           (flags & CURLU_NO_DEFAULT_PORT))
          port = NULL;
      }

      if(h && !(h->flags & PROTOPT_URLOPTIONS))
        options = NULL;

      if((u->host[0] == '[') && u->zoneid) {
        /* make it '[ host %25 zoneid ]' */
        size_t hostlen = strlen(u->host);
        size_t alen = hostlen + 3 + strlen(u->zoneid) + 1;
        allochost = malloc(alen);
        if(!allochost)
          return CURLUE_OUT_OF_MEMORY;
        memcpy(allochost, u->host, hostlen - 1);
        msnprintf(&allochost[hostlen - 1], alen - hostlen + 1,
                  "%%25%s]", u->zoneid);
      }

      url = aprintf("%s://%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
                    scheme,
                    u->user ? u->user : "",
                    u->password ? ":": "",
                    u->password ? u->password : "",
                    options ? ";" : "",
                    options ? options : "",
                    (u->user || u->password || options) ? "@": "",
                    allochost ? allochost : u->host,
                    port ? ":": "",
                    port ? port : "",
                    (u->path && (u->path[0] != '/')) ? "/": "",
                    u->path ? u->path : "/",
                    (u->query && u->query[0]) ? "?": "",
                    (u->query && u->query[0]) ? u->query : "",
                    u->fragment? "#": "",
                    u->fragment? u->fragment : "");
      free(allochost);
    }
    if(!url)
      return CURLUE_OUT_OF_MEMORY;
    *part = url;
    return CURLUE_OK;
  }
  default:
    ptr = NULL;
    break;
  }
  if(ptr) {
    *part = strdup(ptr);
    if(!*part)
      return CURLUE_OUT_OF_MEMORY;
    if(plusdecode) {
      /* convert + to space */
      char *plus;
      for(plus = *part; *plus; ++plus) {
        if(*plus == '+')
          *plus = ' ';
      }
    }
    if(urldecode) {
      char *decoded;
      size_t dlen;
      CURLcode res = Curl_urldecode(NULL, *part, 0, &decoded, &dlen, TRUE);
      free(*part);
      if(res) {
        *part = NULL;
        return CURLUE_URLDECODE;
      }
      *part = decoded;
    }
    return CURLUE_OK;
  }
  else
    return ifmissing;
}