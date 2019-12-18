#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {int dummy; } ;
struct TYPE_19__ {int kind; int /*<<< orphan*/  filename; int /*<<< orphan*/  name; int /*<<< orphan*/  mimetype; int /*<<< orphan*/  encoder; scalar_t__ userheaders; struct TYPE_19__* nextpart; scalar_t__ arg; int /*<<< orphan*/  easy; int /*<<< orphan*/  freefunc; int /*<<< orphan*/  seekfunc; int /*<<< orphan*/  readfunc; int /*<<< orphan*/  datasize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ curl_mimepart ;
struct TYPE_20__ {TYPE_1__* firstpart; } ;
typedef  TYPE_2__ curl_mime ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_READ_ERROR ; 
 int /*<<< orphan*/  Curl_mime_cleanpart (TYPE_1__*) ; 
 struct curl_slist* Curl_slist_duplicate (scalar_t__) ; 
 int /*<<< orphan*/  DEBUGASSERT (TYPE_1__*) ; 
#define  MIMEKIND_CALLBACK 132 
#define  MIMEKIND_DATA 131 
#define  MIMEKIND_FILE 130 
#define  MIMEKIND_MULTIPART 129 
#define  MIMEKIND_NONE 128 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curl_mime_addpart (TYPE_2__*) ; 
 scalar_t__ curl_mime_data (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ curl_mime_data_cb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ curl_mime_filedata (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_filename (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_headers (TYPE_1__*,struct curl_slist*,int /*<<< orphan*/ ) ; 
 TYPE_2__* curl_mime_init (int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_subparts (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ curl_mime_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 

CURLcode Curl_mime_duppart(curl_mimepart *dst, const curl_mimepart *src)
{
  curl_mime *mime;
  curl_mimepart *d;
  const curl_mimepart *s;
  CURLcode res = CURLE_OK;

  DEBUGASSERT(dst);

  /* Duplicate content. */
  switch(src->kind) {
  case MIMEKIND_NONE:
    break;
  case MIMEKIND_DATA:
    res = curl_mime_data(dst, src->data, (size_t) src->datasize);
    break;
  case MIMEKIND_FILE:
    res = curl_mime_filedata(dst, src->data);
    /* Do not abort duplication if file is not readable. */
    if(res == CURLE_READ_ERROR)
      res = CURLE_OK;
    break;
  case MIMEKIND_CALLBACK:
    res = curl_mime_data_cb(dst, src->datasize, src->readfunc,
                            src->seekfunc, src->freefunc, src->arg);
    break;
  case MIMEKIND_MULTIPART:
    /* No one knows about the cloned subparts, thus always attach ownership
       to the part. */
    mime = curl_mime_init(dst->easy);
    res = mime? curl_mime_subparts(dst, mime): CURLE_OUT_OF_MEMORY;

    /* Duplicate subparts. */
    for(s = ((curl_mime *) src->arg)->firstpart; !res && s; s = s->nextpart) {
      d = curl_mime_addpart(mime);
      res = d? Curl_mime_duppart(d, s): CURLE_OUT_OF_MEMORY;
    }
    break;
  default:  /* Invalid kind: should not occur. */
    res = CURLE_BAD_FUNCTION_ARGUMENT;  /* Internal error? */
    break;
  }

  /* Duplicate headers. */
  if(!res && src->userheaders) {
    struct curl_slist *hdrs = Curl_slist_duplicate(src->userheaders);

    if(!hdrs)
      res = CURLE_OUT_OF_MEMORY;
    else {
      /* No one but this procedure knows about the new header list,
         so always take ownership. */
      res = curl_mime_headers(dst, hdrs, TRUE);
      if(res)
        curl_slist_free_all(hdrs);
    }
  }

  if(!res) {
    /* Duplicate other fields. */
    dst->encoder = src->encoder;
    res = curl_mime_type(dst, src->mimetype);
  }
  if(!res)
    res = curl_mime_name(dst, src->name);
  if(!res)
    res = curl_mime_filename(dst, src->filename);

  /* If an error occurred, rollback. */
  if(res)
    Curl_mime_cleanpart(dst);

  return res;
}