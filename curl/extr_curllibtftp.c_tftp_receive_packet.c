#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int rbytes; int remote_addrlen; short event; TYPE_5__ rpacket; int /*<<< orphan*/  error; int /*<<< orphan*/  block; int /*<<< orphan*/  remote_addr; scalar_t__ blksize; int /*<<< orphan*/  sockfd; } ;
typedef  TYPE_2__ tftp_state_data_t ;
typedef  short tftp_event_t ;
typedef  int /*<<< orphan*/  tftp_error_t ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {scalar_t__ tftpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct SingleRequest {int bytecount; } ;
struct Curl_sockaddr_storage {int dummy; } ;
struct Curl_easy {struct SingleRequest req; } ;
typedef  int /*<<< orphan*/  fromaddr ;
typedef  int curl_socklen_t ;
typedef  int /*<<< orphan*/  curl_off_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_BODY ; 
 int /*<<< orphan*/  CURLE_ABORTED_BY_CALLBACK ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadCounter (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_pgrsUpdate (struct connectdata*) ; 
 size_t Curl_strnlen (char*,size_t) ; 
 unsigned short NEXT_BLOCKNUM (int /*<<< orphan*/ ) ; 
#define  TFTP_EVENT_ACK 133 
#define  TFTP_EVENT_DATA 132 
#define  TFTP_EVENT_ERROR 131 
#define  TFTP_EVENT_OACK 130 
#define  TFTP_EVENT_RRQ 129 
 short TFTP_EVENT_TIMEOUT ; 
#define  TFTP_EVENT_WRQ 128 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 unsigned short getrpacketblock (TYPE_5__*) ; 
 unsigned short getrpacketevent (TYPE_5__*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct Curl_sockaddr_storage*,int) ; 
 scalar_t__ recvfrom (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  tftp_parse_option_ack (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  tftp_state_machine (TYPE_2__*,int const) ; 

__attribute__((used)) static CURLcode tftp_receive_packet(struct connectdata *conn)
{
  struct Curl_sockaddr_storage fromaddr;
  curl_socklen_t        fromlen;
  CURLcode              result = CURLE_OK;
  struct Curl_easy  *data = conn->data;
  tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;
  struct SingleRequest  *k = &data->req;

  /* Receive the packet */
  fromlen = sizeof(fromaddr);
  state->rbytes = (int)recvfrom(state->sockfd,
                                (void *)state->rpacket.data,
                                state->blksize + 4,
                                0,
                                (struct sockaddr *)&fromaddr,
                                &fromlen);
  if(state->remote_addrlen == 0) {
    memcpy(&state->remote_addr, &fromaddr, fromlen);
    state->remote_addrlen = fromlen;
  }

  /* Sanity check packet length */
  if(state->rbytes < 4) {
    failf(data, "Received too short packet");
    /* Not a timeout, but how best to handle it? */
    state->event = TFTP_EVENT_TIMEOUT;
  }
  else {
    /* The event is given by the TFTP packet time */
    unsigned short event = getrpacketevent(&state->rpacket);
    state->event = (tftp_event_t)event;

    switch(state->event) {
    case TFTP_EVENT_DATA:
      /* Don't pass to the client empty or retransmitted packets */
      if(state->rbytes > 4 &&
         (NEXT_BLOCKNUM(state->block) == getrpacketblock(&state->rpacket))) {
        result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                   (char *)state->rpacket.data + 4,
                                   state->rbytes-4);
        if(result) {
          tftp_state_machine(state, TFTP_EVENT_ERROR);
          return result;
        }
        k->bytecount += state->rbytes-4;
        Curl_pgrsSetDownloadCounter(data, (curl_off_t) k->bytecount);
      }
      break;
    case TFTP_EVENT_ERROR:
    {
      unsigned short error = getrpacketblock(&state->rpacket);
      char *str = (char *)state->rpacket.data + 4;
      size_t strn = state->rbytes - 4;
      state->error = (tftp_error_t)error;
      if(Curl_strnlen(str, strn) < strn)
        infof(data, "TFTP error: %s\n", str);
      break;
    }
    case TFTP_EVENT_ACK:
      break;
    case TFTP_EVENT_OACK:
      result = tftp_parse_option_ack(state,
                                     (const char *)state->rpacket.data + 2,
                                     state->rbytes-2);
      if(result)
        return result;
      break;
    case TFTP_EVENT_RRQ:
    case TFTP_EVENT_WRQ:
    default:
      failf(data, "%s", "Internal error: Unexpected packet");
      break;
    }

    /* Update the progress meter */
    if(Curl_pgrsUpdate(conn)) {
      tftp_state_machine(state, TFTP_EVENT_ERROR);
      return CURLE_ABORTED_BY_CALLBACK;
    }
  }
  return result;
}