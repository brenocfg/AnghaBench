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
typedef  scalar_t__ timediff_t ;
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_2__ {scalar_t__ accepttimeout; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ AcceptServerConnect (struct connectdata*) ; 
 scalar_t__ CURLE_FTP_ACCEPT_TIMEOUT ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_expire (struct Curl_easy*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_pgrsTime (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEFAULT_ACCEPT_TIMEOUT ; 
 int FALSE ; 
 scalar_t__ InitiateTransfer (struct connectdata*) ; 
 scalar_t__ ReceivedServerConnect (struct connectdata*,int*) ; 
 int /*<<< orphan*/  TIMER_STARTACCEPT ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 scalar_t__ ftp_timeleft_accept (struct Curl_easy*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 

__attribute__((used)) static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
{
  struct Curl_easy *data = conn->data;
  timediff_t timeout_ms;
  CURLcode result = CURLE_OK;

  *connected = FALSE;
  infof(data, "Preparing for accepting server on data port\n");

  /* Save the time we start accepting server connect */
  Curl_pgrsTime(data, TIMER_STARTACCEPT);

  timeout_ms = ftp_timeleft_accept(data);
  if(timeout_ms < 0) {
    /* if a timeout was already reached, bail out */
    failf(data, "Accept timeout occurred while waiting server connect");
    return CURLE_FTP_ACCEPT_TIMEOUT;
  }

  /* see if the connection request is already here */
  result = ReceivedServerConnect(conn, connected);
  if(result)
    return result;

  if(*connected) {
    result = AcceptServerConnect(conn);
    if(result)
      return result;

    result = InitiateTransfer(conn);
    if(result)
      return result;
  }
  else {
    /* Add timeout to multi handle and break out of the loop */
    if(*connected == FALSE) {
      Curl_expire(data, data->set.accepttimeout > 0 ?
                  data->set.accepttimeout: DEFAULT_ACCEPT_TIMEOUT, 0);
    }
  }

  return result;
}