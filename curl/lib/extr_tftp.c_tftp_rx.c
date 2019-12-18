#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {int block; int retries; int retry_max; void* state; int /*<<< orphan*/  remote_addrlen; int /*<<< orphan*/  remote_addr; TYPE_4__ spacket; int /*<<< orphan*/  sockfd; int /*<<< orphan*/  error; int /*<<< orphan*/  rx_time; int /*<<< orphan*/  blksize; int /*<<< orphan*/  rbytes; int /*<<< orphan*/  rpacket; TYPE_1__* conn; } ;
typedef  TYPE_2__ tftp_state_data_t ;
typedef  int tftp_event_t ;
struct sockaddr {int dummy; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {struct Curl_easy* data; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  CURLE_TFTP_ILLEGAL ; 
 char* Curl_strerror (int /*<<< orphan*/ ,char*,int) ; 
 int NEXT_BLOCKNUM (int) ; 
 int /*<<< orphan*/  SEND_4TH_ARG ; 
 int /*<<< orphan*/  SOCKERRNO ; 
 int STRERROR_LEN ; 
 int /*<<< orphan*/  TFTP_ERR_TIMEOUT ; 
 int const TFTP_EVENT_ACK ; 
#define  TFTP_EVENT_DATA 131 
#define  TFTP_EVENT_ERROR 130 
#define  TFTP_EVENT_OACK 129 
#define  TFTP_EVENT_TIMEOUT 128 
 void* TFTP_STATE_FIN ; 
 void* TFTP_STATE_RX ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,char*) ; 
 int getrpacketblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int,...) ; 
 int /*<<< orphan*/  sendto (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpacketblock (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  setpacketevent (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode tftp_rx(tftp_state_data_t *state, tftp_event_t event)
{
  ssize_t sbytes;
  int rblock;
  struct Curl_easy *data = state->conn->data;
  char buffer[STRERROR_LEN];

  switch(event) {

  case TFTP_EVENT_DATA:
    /* Is this the block we expect? */
    rblock = getrpacketblock(&state->rpacket);
    if(NEXT_BLOCKNUM(state->block) == rblock) {
      /* This is the expected block.  Reset counters and ACK it. */
      state->retries = 0;
    }
    else if(state->block == rblock) {
      /* This is the last recently received block again. Log it and ACK it
         again. */
      infof(data, "Received last DATA packet block %d again.\n", rblock);
    }
    else {
      /* totally unexpected, just log it */
      infof(data,
            "Received unexpected DATA packet block %d, expecting block %d\n",
            rblock, NEXT_BLOCKNUM(state->block));
      break;
    }

    /* ACK this block. */
    state->block = (unsigned short)rblock;
    setpacketevent(&state->spacket, TFTP_EVENT_ACK);
    setpacketblock(&state->spacket, state->block);
    sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                    4, SEND_4TH_ARG,
                    (struct sockaddr *)&state->remote_addr,
                    state->remote_addrlen);
    if(sbytes < 0) {
      failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
      return CURLE_SEND_ERROR;
    }

    /* Check if completed (That is, a less than full packet is received) */
    if(state->rbytes < (ssize_t)state->blksize + 4) {
      state->state = TFTP_STATE_FIN;
    }
    else {
      state->state = TFTP_STATE_RX;
    }
    time(&state->rx_time);
    break;

  case TFTP_EVENT_OACK:
    /* ACK option acknowledgement so we can move on to data */
    state->block = 0;
    state->retries = 0;
    setpacketevent(&state->spacket, TFTP_EVENT_ACK);
    setpacketblock(&state->spacket, state->block);
    sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                    4, SEND_4TH_ARG,
                    (struct sockaddr *)&state->remote_addr,
                    state->remote_addrlen);
    if(sbytes < 0) {
      failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
      return CURLE_SEND_ERROR;
    }

    /* we're ready to RX data */
    state->state = TFTP_STATE_RX;
    time(&state->rx_time);
    break;

  case TFTP_EVENT_TIMEOUT:
    /* Increment the retry count and fail if over the limit */
    state->retries++;
    infof(data,
          "Timeout waiting for block %d ACK.  Retries = %d\n",
          NEXT_BLOCKNUM(state->block), state->retries);
    if(state->retries > state->retry_max) {
      state->error = TFTP_ERR_TIMEOUT;
      state->state = TFTP_STATE_FIN;
    }
    else {
      /* Resend the previous ACK */
      sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                      4, SEND_4TH_ARG,
                      (struct sockaddr *)&state->remote_addr,
                      state->remote_addrlen);
      if(sbytes<0) {
        failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
        return CURLE_SEND_ERROR;
      }
    }
    break;

  case TFTP_EVENT_ERROR:
    setpacketevent(&state->spacket, TFTP_EVENT_ERROR);
    setpacketblock(&state->spacket, state->block);
    (void)sendto(state->sockfd, (void *)state->spacket.data,
                 4, SEND_4TH_ARG,
                 (struct sockaddr *)&state->remote_addr,
                 state->remote_addrlen);
    /* don't bother with the return code, but if the socket is still up we
     * should be a good TFTP client and let the server know we're done */
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(data, "%s", "tftp_rx: internal error");
    return CURLE_TFTP_ILLEGAL; /* not really the perfect return code for
                                  this */
  }
  return CURLE_OK;
}