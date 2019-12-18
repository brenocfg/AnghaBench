#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connectdata {struct Curl_easy* data; } ;
struct IMAP {char* mailbox; char* uidvalidity; char* uid; char* mindex; char* section; char* partial; int /*<<< orphan*/  query; } ;
struct TYPE_5__ {char* path; } ;
struct TYPE_6__ {int /*<<< orphan*/  uh; TYPE_2__ up; } ;
struct TYPE_4__ {struct IMAP* protop; } ;
struct Curl_easy {TYPE_3__ state; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  CURLUPART_QUERY ; 
 int /*<<< orphan*/  CURLU_URLDECODE ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,char const*,int,char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_url_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ imap_is_bchar (char const) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char*,char*) ; 
 scalar_t__ strcasecompare (char*,char*) ; 

__attribute__((used)) static CURLcode imap_parse_url_path(struct connectdata *conn)
{
  /* The imap struct is already initialised in imap_connect() */
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  const char *begin = &data->state.up.path[1]; /* skip leading slash */
  const char *ptr = begin;

  /* See how much of the URL is a valid path and decode it */
  while(imap_is_bchar(*ptr))
    ptr++;

  if(ptr != begin) {
    /* Remove the trailing slash if present */
    const char *end = ptr;
    if(end > begin && end[-1] == '/')
      end--;

    result = Curl_urldecode(data, begin, end - begin, &imap->mailbox, NULL,
                            TRUE);
    if(result)
      return result;
  }
  else
    imap->mailbox = NULL;

  /* There can be any number of parameters in the form ";NAME=VALUE" */
  while(*ptr == ';') {
    char *name;
    char *value;
    size_t valuelen;

    /* Find the length of the name parameter */
    begin = ++ptr;
    while(*ptr && *ptr != '=')
      ptr++;

    if(!*ptr)
      return CURLE_URL_MALFORMAT;

    /* Decode the name parameter */
    result = Curl_urldecode(data, begin, ptr - begin, &name, NULL, TRUE);
    if(result)
      return result;

    /* Find the length of the value parameter */
    begin = ++ptr;
    while(imap_is_bchar(*ptr))
      ptr++;

    /* Decode the value parameter */
    result = Curl_urldecode(data, begin, ptr - begin, &value, &valuelen, TRUE);
    if(result) {
      free(name);
      return result;
    }

    DEBUGF(infof(conn->data, "IMAP URL parameter '%s' = '%s'\n", name, value));

    /* Process the known hierarchical parameters (UIDVALIDITY, UID, SECTION and
       PARTIAL) stripping of the trailing slash character if it is present.

       Note: Unknown parameters trigger a URL_MALFORMAT error. */
    if(strcasecompare(name, "UIDVALIDITY") && !imap->uidvalidity) {
      if(valuelen > 0 && value[valuelen - 1] == '/')
        value[valuelen - 1] = '\0';

      imap->uidvalidity = value;
      value = NULL;
    }
    else if(strcasecompare(name, "UID") && !imap->uid) {
      if(valuelen > 0 && value[valuelen - 1] == '/')
        value[valuelen - 1] = '\0';

      imap->uid = value;
      value = NULL;
    }
    else if(strcasecompare(name, "MAILINDEX") && !imap->mindex) {
      if(valuelen > 0 && value[valuelen - 1] == '/')
        value[valuelen - 1] = '\0';

      imap->mindex = value;
      value = NULL;
    }
    else if(strcasecompare(name, "SECTION") && !imap->section) {
      if(valuelen > 0 && value[valuelen - 1] == '/')
        value[valuelen - 1] = '\0';

      imap->section = value;
      value = NULL;
    }
    else if(strcasecompare(name, "PARTIAL") && !imap->partial) {
      if(valuelen > 0 && value[valuelen - 1] == '/')
        value[valuelen - 1] = '\0';

      imap->partial = value;
      value = NULL;
    }
    else {
      free(name);
      free(value);

      return CURLE_URL_MALFORMAT;
    }

    free(name);
    free(value);
  }

  /* Does the URL contain a query parameter? Only valid when we have a mailbox
     and no UID as per RFC-5092 */
  if(imap->mailbox && !imap->uid && !imap->mindex) {
    /* Get the query parameter, URL decoded */
    (void)curl_url_get(data->state.uh, CURLUPART_QUERY, &imap->query,
                       CURLU_URLDECODE);
  }

  /* Any extra stuff at the end of the URL is an error */
  if(*ptr)
    return CURLE_URL_MALFORMAT;

  return CURLE_OK;
}