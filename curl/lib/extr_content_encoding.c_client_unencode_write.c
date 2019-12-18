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
struct SingleRequest {scalar_t__ ignorebody; } ;
struct Curl_easy {struct SingleRequest req; } ;
typedef  int /*<<< orphan*/  contenc_writer ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_BODY ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static CURLcode client_unencode_write(struct connectdata *conn,
                                      contenc_writer *writer,
                                      const char *buf, size_t nbytes)
{
  struct Curl_easy *data = conn->data;
  struct SingleRequest *k = &data->req;

  (void) writer;

  if(!nbytes || k->ignorebody)
    return CURLE_OK;

  return Curl_client_write(conn, CLIENTWRITE_BODY, (char *) buf, nbytes);
}