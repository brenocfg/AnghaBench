#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* referer; void* url; int /*<<< orphan*/ * cookielist; void* referer_alloc; void* url_alloc; } ;
struct TYPE_9__ {void* headerbuff; void* buffer; int /*<<< orphan*/  resolver; int /*<<< orphan*/ * lastconnect; int /*<<< orphan*/ * conn_cache; scalar_t__ headersize; } ;
struct TYPE_8__ {scalar_t__* str; int /*<<< orphan*/  cookiesession; scalar_t__ buffer_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  callback; int /*<<< orphan*/  flags; } ;
struct Curl_easy {TYPE_4__ change; TYPE_3__ state; int /*<<< orphan*/  magic; TYPE_2__ set; TYPE_5__* cookies; TYPE_1__ progress; } ;
struct TYPE_11__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLEASY_MAGIC_NUMBER ; 
 int /*<<< orphan*/  Curl_convert_setup (struct Curl_easy*) ; 
 TYPE_5__* Curl_cookie_init (struct Curl_easy*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_freeset (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_initinfo (struct Curl_easy*) ; 
 scalar_t__ Curl_resolver_duphandle (struct Curl_easy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_safefree (void*) ; 
 int /*<<< orphan*/ * Curl_slist_duplicate (int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_ssl_set_engine (struct Curl_easy*,scalar_t__) ; 
 scalar_t__ HEADERSIZE ; 
 size_t STRING_SSL_ENGINE ; 
 void* TRUE ; 
 struct Curl_easy* calloc (int,int) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 
 scalar_t__ dupset (struct Curl_easy*,struct Curl_easy*) ; 
 int /*<<< orphan*/  free (struct Curl_easy*) ; 
 void* malloc (scalar_t__) ; 
 void* strdup (void*) ; 

struct Curl_easy *curl_easy_duphandle(struct Curl_easy *data)
{
  struct Curl_easy *outcurl = calloc(1, sizeof(struct Curl_easy));
  if(NULL == outcurl)
    goto fail;

  /*
   * We setup a few buffers we need. We should probably make them
   * get setup on-demand in the code, as that would probably decrease
   * the likeliness of us forgetting to init a buffer here in the future.
   */
  outcurl->set.buffer_size = data->set.buffer_size;
  outcurl->state.buffer = malloc(outcurl->set.buffer_size + 1);
  if(!outcurl->state.buffer)
    goto fail;

  outcurl->state.headerbuff = malloc(HEADERSIZE);
  if(!outcurl->state.headerbuff)
    goto fail;
  outcurl->state.headersize = HEADERSIZE;

  /* copy all userdefined values */
  if(dupset(outcurl, data))
    goto fail;

  /* the connection cache is setup on demand */
  outcurl->state.conn_cache = NULL;

  outcurl->state.lastconnect = NULL;

  outcurl->progress.flags    = data->progress.flags;
  outcurl->progress.callback = data->progress.callback;

  if(data->cookies) {
    /* If cookies are enabled in the parent handle, we enable them
       in the clone as well! */
    outcurl->cookies = Curl_cookie_init(data,
                                        data->cookies->filename,
                                        outcurl->cookies,
                                        data->set.cookiesession);
    if(!outcurl->cookies)
      goto fail;
  }

  /* duplicate all values in 'change' */
  if(data->change.cookielist) {
    outcurl->change.cookielist =
      Curl_slist_duplicate(data->change.cookielist);
    if(!outcurl->change.cookielist)
      goto fail;
  }

  if(data->change.url) {
    outcurl->change.url = strdup(data->change.url);
    if(!outcurl->change.url)
      goto fail;
    outcurl->change.url_alloc = TRUE;
  }

  if(data->change.referer) {
    outcurl->change.referer = strdup(data->change.referer);
    if(!outcurl->change.referer)
      goto fail;
    outcurl->change.referer_alloc = TRUE;
  }

  /* Reinitialize an SSL engine for the new handle
   * note: the engine name has already been copied by dupset */
  if(outcurl->set.str[STRING_SSL_ENGINE]) {
    if(Curl_ssl_set_engine(outcurl, outcurl->set.str[STRING_SSL_ENGINE]))
      goto fail;
  }

  /* Clone the resolver handle, if present, for the new handle */
  if(Curl_resolver_duphandle(outcurl,
                             &outcurl->state.resolver,
                             data->state.resolver))
    goto fail;

  Curl_convert_setup(outcurl);

  Curl_initinfo(outcurl);

  outcurl->magic = CURLEASY_MAGIC_NUMBER;

  /* we reach this point and thus we are OK */

  return outcurl;

  fail:

  if(outcurl) {
    curl_slist_free_all(outcurl->change.cookielist);
    outcurl->change.cookielist = NULL;
    Curl_safefree(outcurl->state.buffer);
    Curl_safefree(outcurl->state.headerbuff);
    Curl_safefree(outcurl->change.url);
    Curl_safefree(outcurl->change.referer);
    Curl_freeset(outcurl);
    free(outcurl);
  }

  return NULL;
}