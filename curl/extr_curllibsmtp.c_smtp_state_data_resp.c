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
struct TYPE_2__ {int /*<<< orphan*/  infilesize; } ;
struct Curl_easy {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  smtpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadSize (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 int /*<<< orphan*/  SMTP_STOP ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_state_data_resp(struct connectdata *conn, int smtpcode,
                                     smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(smtpcode != 354) {
    failf(data, "DATA failed: %d", smtpcode);
    result = CURLE_SEND_ERROR;
  }
  else {
    /* Set the progress upload size */
    Curl_pgrsSetUploadSize(data, data->state.infilesize);

    /* SMTP upload */
    Curl_setup_transfer(data, -1, -1, FALSE, FIRSTSOCKET);

    /* End of DO phase */
    state(conn, SMTP_STOP);
  }

  return result;
}