#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  close; int /*<<< orphan*/  protoconnstart; } ;
struct connectdata {TYPE_2__ bits; TYPE_1__* handler; } ;
struct TYPE_6__ {scalar_t__ httpversion; } ;
struct Curl_easy {TYPE_3__ set; int /*<<< orphan*/  multi; } ;
struct TYPE_4__ {int protocol; } ;

/* Variables and functions */
 int CURLPIPE_MULTIPLEX ; 
 scalar_t__ CURL_HTTP_VERSION_2 ; 
 scalar_t__ Curl_multiplex_wanted (int /*<<< orphan*/ ) ; 
 int PROTO_FAMILY_HTTP ; 

__attribute__((used)) static int IsMultiplexingPossible(const struct Curl_easy *handle,
                                  const struct connectdata *conn)
{
  int avail = 0;

  /* If a HTTP protocol and multiplexing is enabled */
  if((conn->handler->protocol & PROTO_FAMILY_HTTP) &&
     (!conn->bits.protoconnstart || !conn->bits.close)) {

    if(Curl_multiplex_wanted(handle->multi) &&
       (handle->set.httpversion >= CURL_HTTP_VERSION_2))
      /* allows HTTP/2 */
      avail |= CURLPIPE_MULTIPLEX;
  }
  return avail;
}