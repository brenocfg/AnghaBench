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
struct connectdata {struct Curl_easy* data; } ;
struct SingleRequest {int /*<<< orphan*/ * writer_stack; int /*<<< orphan*/  chunk; } ;
struct Curl_easy {struct SingleRequest req; } ;
typedef  int /*<<< orphan*/  content_encoding ;
typedef  int /*<<< orphan*/  contenc_writer ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_httpchunk_init (struct connectdata*) ; 
 scalar_t__ ISSPACE (char const) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  const client_encoding ; 
 int /*<<< orphan*/  error_encoding ; 
 int /*<<< orphan*/ * find_encoding (char const*,size_t) ; 
 void* new_unencoding_writer (struct connectdata*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecompare (char const*,char*,int) ; 

CURLcode Curl_build_unencoding_stack(struct connectdata *conn,
                                     const char *enclist, int maybechunked)
{
  struct Curl_easy *data = conn->data;
  struct SingleRequest *k = &data->req;

  do {
    const char *name;
    size_t namelen;

    /* Parse a single encoding name. */
    while(ISSPACE(*enclist) || *enclist == ',')
      enclist++;

    name = enclist;

    for(namelen = 0; *enclist && *enclist != ','; enclist++)
      if(!ISSPACE(*enclist))
        namelen = enclist - name + 1;

    /* Special case: chunked encoding is handled at the reader level. */
    if(maybechunked && namelen == 7 && strncasecompare(name, "chunked", 7)) {
      k->chunk = TRUE;             /* chunks coming our way. */
      Curl_httpchunk_init(conn);   /* init our chunky engine. */
    }
    else if(namelen) {
      const content_encoding *encoding = find_encoding(name, namelen);
      contenc_writer *writer;

      if(!k->writer_stack) {
        k->writer_stack = new_unencoding_writer(conn, &client_encoding, NULL);

        if(!k->writer_stack)
          return CURLE_OUT_OF_MEMORY;
      }

      if(!encoding)
        encoding = &error_encoding;  /* Defer error at stack use. */

      /* Stack the unencoding stage. */
      writer = new_unencoding_writer(conn, encoding, k->writer_stack);
      if(!writer)
        return CURLE_OUT_OF_MEMORY;
      k->writer_stack = writer;
    }
  } while(*enclist);

  return CURLE_OK;
}