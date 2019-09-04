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
struct connectdata {int dummy; } ;
typedef  int /*<<< orphan*/  imapstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UPLOAD_FAILED ; 
 int IMAP_RESP_OK ; 
 int /*<<< orphan*/  IMAP_STOP ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_state_append_final_resp(struct connectdata *conn,
                                             int imapcode,
                                             imapstate instate)
{
  CURLcode result = CURLE_OK;

  (void)instate; /* No use for this yet */

  if(imapcode != IMAP_RESP_OK)
    result = CURLE_UPLOAD_FAILED;
  else
    /* End of DONE phase */
    state(conn, IMAP_STOP);

  return result;
}