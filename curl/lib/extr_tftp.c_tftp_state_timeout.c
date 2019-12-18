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
typedef  scalar_t__ time_t ;
struct TYPE_4__ {scalar_t__ max_time; scalar_t__ rx_time; scalar_t__ retry_time; int /*<<< orphan*/  state; int /*<<< orphan*/  error; } ;
typedef  TYPE_2__ tftp_state_data_t ;
typedef  int /*<<< orphan*/  tftp_event_t ;
struct TYPE_3__ {scalar_t__ tftpc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFTP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  TFTP_EVENT_NONE ; 
 int /*<<< orphan*/  TFTP_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  TFTP_STATE_FIN ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,long,long) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

__attribute__((used)) static long tftp_state_timeout(struct connectdata *conn, tftp_event_t *event)
{
  time_t                current;
  tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;

  if(event)
    *event = TFTP_EVENT_NONE;

  time(&current);
  if(current > state->max_time) {
    DEBUGF(infof(conn->data, "timeout: %ld > %ld\n",
                 (long)current, (long)state->max_time));
    state->error = TFTP_ERR_TIMEOUT;
    state->state = TFTP_STATE_FIN;
    return 0;
  }
  if(current > state->rx_time + state->retry_time) {
    if(event)
      *event = TFTP_EVENT_TIMEOUT;
    time(&state->rx_time); /* update even though we received nothing */
  }

  /* there's a typecast below here since 'time_t' may in fact be larger than
     'long', but we estimate that a 'long' will still be able to hold number
     of seconds even if "only" 32 bit */
  return (long)(state->max_time - current);
}