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
struct TYPE_2__ {scalar_t__ rewindaftersend; } ;
struct connectdata {TYPE_1__ bits; } ;
struct SingleRequest {int /*<<< orphan*/  keepon; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_http2_done_sending (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_quic_done_sending (struct connectdata*) ; 
 scalar_t__ Curl_readrewind (struct connectdata*) ; 
 int /*<<< orphan*/  KEEP_SEND ; 

CURLcode Curl_done_sending(struct connectdata *conn,
                           struct SingleRequest *k)
{
  k->keepon &= ~KEEP_SEND; /* we're done writing */

  /* These functions should be moved into the handler struct! */
  Curl_http2_done_sending(conn);
  Curl_quic_done_sending(conn);

  if(conn->bits.rewindaftersend) {
    CURLcode result = Curl_readrewind(conn);
    if(result)
      return result;
  }
  return CURLE_OK;
}