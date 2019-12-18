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
struct POP3 {int /*<<< orphan*/  transfer; int /*<<< orphan*/  custom; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {struct POP3* protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPTRANSFER_BODY ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 

__attribute__((used)) static CURLcode pop3_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;

  (void)premature;

  if(!pop3)
    return CURLE_OK;

  if(status) {
    connclose(conn, "POP3 done with bad status");
    result = status;         /* use the already set error code */
  }

  /* Cleanup our per-request based variables */
  Curl_safefree(pop3->id);
  Curl_safefree(pop3->custom);

  /* Clear the transfer mode for the next request */
  pop3->transfer = FTPTRANSFER_BODY;

  return result;
}