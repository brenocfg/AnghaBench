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
struct connectdata {struct Curl_easy* data; } ;
struct HTTP {int /*<<< orphan*/  form; } ;
struct TYPE_2__ {struct HTTP* protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_INUSE (struct connectdata*) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_http2_setup_conn (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_http2_setup_req (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_mime_initpart (int /*<<< orphan*/ *,struct Curl_easy*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int /*<<< orphan*/ ) ; 
 struct HTTP* calloc (int,int) ; 

__attribute__((used)) static CURLcode http_setup_conn(struct connectdata *conn)
{
  /* allocate the HTTP-specific struct for the Curl_easy, only to survive
     during this request */
  struct HTTP *http;
  struct Curl_easy *data = conn->data;
  DEBUGASSERT(data->req.protop == NULL);

  http = calloc(1, sizeof(struct HTTP));
  if(!http)
    return CURLE_OUT_OF_MEMORY;

  Curl_mime_initpart(&http->form, conn->data);
  data->req.protop = http;

  if(!CONN_INUSE(conn))
    /* if not already multi-using, setup connection details */
    Curl_http2_setup_conn(conn);
  Curl_http2_setup_req(data);
  return CURLE_OK;
}