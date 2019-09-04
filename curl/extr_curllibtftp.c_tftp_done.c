#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_2__ tftp_state_data_t ;
struct TYPE_3__ {scalar_t__ tftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_ABORTED_BY_CALLBACK ; 
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ Curl_pgrsDone (struct connectdata*) ; 
 int /*<<< orphan*/  tftp_translate_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode tftp_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  tftp_state_data_t *state = (tftp_state_data_t *)conn->proto.tftpc;

  (void)status; /* unused */
  (void)premature; /* not used */

  if(Curl_pgrsDone(conn))
    return CURLE_ABORTED_BY_CALLBACK;

  /* If we have encountered an error */
  if(state)
    result = tftp_translate_code(state->error);

  return result;
}