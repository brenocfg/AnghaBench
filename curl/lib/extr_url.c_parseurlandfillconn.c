#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* rawalloc; void* name; } ;
struct TYPE_10__ {void* ipv6_ip; void* user_passwd; } ;
struct connectdata {scalar_t__ scope_id; TYPE_1__ host; TYPE_4__ bits; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  port; void* options; void* passwd; void* user; } ;
struct TYPE_8__ {scalar_t__ scope_id; scalar_t__ path_as_is; scalar_t__ disallow_username_in_url; scalar_t__ uh; scalar_t__* str; } ;
struct TYPE_11__ {char* scheme; char* user; char* password; char* options; char* hostname; char* path; char* port; char* query; } ;
struct TYPE_12__ {TYPE_5__ up; int /*<<< orphan*/ * uh; } ;
struct TYPE_9__ {char* url; void* url_alloc; } ;
struct Curl_easy {TYPE_2__ set; TYPE_6__ state; TYPE_3__ change; } ;
typedef  scalar_t__ CURLcode ;
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLUE_NO_OPTIONS ; 
 scalar_t__ CURLUE_NO_PASSWORD ; 
 scalar_t__ CURLUE_NO_USER ; 
 int /*<<< orphan*/  CURLUPART_HOST ; 
 int /*<<< orphan*/  CURLUPART_OPTIONS ; 
 int /*<<< orphan*/  CURLUPART_PASSWORD ; 
 int /*<<< orphan*/  CURLUPART_PATH ; 
 int /*<<< orphan*/  CURLUPART_PORT ; 
 int /*<<< orphan*/  CURLUPART_QUERY ; 
 int /*<<< orphan*/  CURLUPART_SCHEME ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int /*<<< orphan*/  CURLUPART_USER ; 
 int /*<<< orphan*/  CURLU_DEFAULT_PORT ; 
 int CURLU_DISALLOW_USER ; 
 int CURLU_GUESS_SCHEME ; 
 int CURLU_NON_SUPPORT_SCHEME ; 
 int CURLU_PATH_AS_IS ; 
 int /*<<< orphan*/  CURLU_URLDECODE ; 
 int /*<<< orphan*/  Curl_is_absolute_url (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_uc_to_curlcode (scalar_t__) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SCHEME_LEN ; 
 size_t STRING_DEFAULT_PROTOCOL ; 
 void* TRUE ; 
 char* aprintf (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/ * curl_url_dup (scalar_t__) ; 
 scalar_t__ curl_url_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  curlx_ultous (unsigned long) ; 
 scalar_t__ findprotocol (struct Curl_easy*,struct connectdata*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char*) ; 
 int /*<<< orphan*/  strcasecompare (char*,char*) ; 
 void* strdup (char*) ; 
 size_t strlen (char*) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up_free (struct Curl_easy*) ; 
 int /*<<< orphan*/  zonefrom_url (int /*<<< orphan*/ *,struct connectdata*) ; 

__attribute__((used)) static CURLcode parseurlandfillconn(struct Curl_easy *data,
                                    struct connectdata *conn)
{
  CURLcode result;
  CURLU *uh;
  CURLUcode uc;
  char *hostname;

  up_free(data); /* cleanup previous leftovers first */

  /* parse the URL */
  if(data->set.uh) {
    uh = data->state.uh = curl_url_dup(data->set.uh);
  }
  else {
    uh = data->state.uh = curl_url();
  }

  if(!uh)
    return CURLE_OUT_OF_MEMORY;

  if(data->set.str[STRING_DEFAULT_PROTOCOL] &&
     !Curl_is_absolute_url(data->change.url, NULL, MAX_SCHEME_LEN)) {
    char *url;
    if(data->change.url_alloc)
      free(data->change.url);
    url = aprintf("%s://%s", data->set.str[STRING_DEFAULT_PROTOCOL],
                  data->change.url);
    if(!url)
      return CURLE_OUT_OF_MEMORY;
    data->change.url = url;
    data->change.url_alloc = TRUE;
  }

  if(!data->set.uh) {
    char *newurl;
    uc = curl_url_set(uh, CURLUPART_URL, data->change.url,
                    CURLU_GUESS_SCHEME |
                    CURLU_NON_SUPPORT_SCHEME |
                    (data->set.disallow_username_in_url ?
                     CURLU_DISALLOW_USER : 0) |
                    (data->set.path_as_is ? CURLU_PATH_AS_IS : 0));
    if(uc) {
      DEBUGF(infof(data, "curl_url_set rejected %s\n", data->change.url));
      return Curl_uc_to_curlcode(uc);
    }

    /* after it was parsed, get the generated normalized version */
    uc = curl_url_get(uh, CURLUPART_URL, &newurl, 0);
    if(uc)
      return Curl_uc_to_curlcode(uc);
    if(data->change.url_alloc)
      free(data->change.url);
    data->change.url = newurl;
    data->change.url_alloc = TRUE;
  }

  uc = curl_url_get(uh, CURLUPART_SCHEME, &data->state.up.scheme, 0);
  if(uc)
    return Curl_uc_to_curlcode(uc);

  result = findprotocol(data, conn, data->state.up.scheme);
  if(result)
    return result;

  uc = curl_url_get(uh, CURLUPART_USER, &data->state.up.user,
                    CURLU_URLDECODE);
  if(!uc) {
    conn->user = strdup(data->state.up.user);
    if(!conn->user)
      return CURLE_OUT_OF_MEMORY;
    conn->bits.user_passwd = TRUE;
  }
  else if(uc != CURLUE_NO_USER)
    return Curl_uc_to_curlcode(uc);

  uc = curl_url_get(uh, CURLUPART_PASSWORD, &data->state.up.password,
                    CURLU_URLDECODE);
  if(!uc) {
    conn->passwd = strdup(data->state.up.password);
    if(!conn->passwd)
      return CURLE_OUT_OF_MEMORY;
    conn->bits.user_passwd = TRUE;
  }
  else if(uc != CURLUE_NO_PASSWORD)
    return Curl_uc_to_curlcode(uc);

  uc = curl_url_get(uh, CURLUPART_OPTIONS, &data->state.up.options,
                    CURLU_URLDECODE);
  if(!uc) {
    conn->options = strdup(data->state.up.options);
    if(!conn->options)
      return CURLE_OUT_OF_MEMORY;
  }
  else if(uc != CURLUE_NO_OPTIONS)
    return Curl_uc_to_curlcode(uc);

  uc = curl_url_get(uh, CURLUPART_HOST, &data->state.up.hostname, 0);
  if(uc) {
    if(!strcasecompare("file", data->state.up.scheme))
      return CURLE_OUT_OF_MEMORY;
  }

  uc = curl_url_get(uh, CURLUPART_PATH, &data->state.up.path, 0);
  if(uc)
    return Curl_uc_to_curlcode(uc);

  uc = curl_url_get(uh, CURLUPART_PORT, &data->state.up.port,
                    CURLU_DEFAULT_PORT);
  if(uc) {
    if(!strcasecompare("file", data->state.up.scheme))
      return CURLE_OUT_OF_MEMORY;
  }
  else {
    unsigned long port = strtoul(data->state.up.port, NULL, 10);
    conn->port = conn->remote_port = curlx_ultous(port);
  }

  (void)curl_url_get(uh, CURLUPART_QUERY, &data->state.up.query, 0);

  hostname = data->state.up.hostname;
  if(hostname && hostname[0] == '[') {
    /* This looks like an IPv6 address literal. See if there is an address
       scope. */
    size_t hlen;
    conn->bits.ipv6_ip = TRUE;
    /* cut off the brackets! */
    hostname++;
    hlen = strlen(hostname);
    hostname[hlen - 1] = 0;

    zonefrom_url(uh, conn);
  }

  /* make sure the connect struct gets its own copy of the host name */
  conn->host.rawalloc = strdup(hostname ? hostname : "");
  if(!conn->host.rawalloc)
    return CURLE_OUT_OF_MEMORY;
  conn->host.name = conn->host.rawalloc;

  if(data->set.scope_id)
    /* Override any scope that was set above.  */
    conn->scope_id = data->set.scope_id;

  return CURLE_OK;
}