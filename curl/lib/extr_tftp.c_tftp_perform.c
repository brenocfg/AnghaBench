#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_2__ tftp_state_data_t ;
struct TYPE_4__ {scalar_t__ tftpc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  TFTP_EVENT_INIT ; 
 scalar_t__ TFTP_STATE_FIN ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tftp_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ tftp_state_machine (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode tftp_perform(struct connectdata *conn, bool *dophase_done)
{
  CURLcode              result = CURLE_OK;
  tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;

  *dophase_done = FALSE;

  result = tftp_state_machine(state, TFTP_EVENT_INIT);

  if((state->state == TFTP_STATE_FIN) || result)
    return result;

  tftp_multi_statemach(conn, dophase_done);

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete\n"));

  return result;
}