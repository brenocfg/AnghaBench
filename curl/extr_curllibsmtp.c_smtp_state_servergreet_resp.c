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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  smtpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_WEIRD_SERVER_REPLY ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  smtp_perform_ehlo (struct connectdata*) ; 

__attribute__((used)) static CURLcode smtp_state_servergreet_resp(struct connectdata *conn,
                                            int smtpcode,
                                            smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(smtpcode/100 != 2) {
    failf(data, "Got unexpected smtp-server response: %d", smtpcode);
    result = CURLE_WEIRD_SERVER_REPLY;
  }
  else
    result = smtp_perform_ehlo(conn);

  return result;
}