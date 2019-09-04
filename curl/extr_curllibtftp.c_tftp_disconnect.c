#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_3__ spacket; TYPE_2__ rpacket; } ;
typedef  TYPE_4__ tftp_state_data_t ;
struct TYPE_6__ {TYPE_4__* tftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 

__attribute__((used)) static CURLcode tftp_disconnect(struct connectdata *conn, bool dead_connection)
{
  tftp_state_data_t *state = conn->proto.tftpc;
  (void) dead_connection;

  /* done, free dynamically allocated pkt buffers */
  if(state) {
    Curl_safefree(state->rpacket.data);
    Curl_safefree(state->spacket.data);
    free(state);
  }

  return CURLE_OK;
}