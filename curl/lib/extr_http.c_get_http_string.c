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
struct TYPE_5__ {scalar_t__ h2; } ;
struct TYPE_6__ {TYPE_2__ httpc; } ;
struct connectdata {int httpversion; TYPE_3__ proto; } ;
struct TYPE_4__ {scalar_t__ httpversion; } ;
struct Curl_easy {TYPE_1__ set; } ;

/* Variables and functions */
 scalar_t__ CURL_HTTP_VERSION_3 ; 
 scalar_t__ use_http_1_1plus (struct Curl_easy const*,struct connectdata const*) ; 

__attribute__((used)) static const char *get_http_string(const struct Curl_easy *data,
                                   const struct connectdata *conn)
{
#ifdef ENABLE_QUIC
  if((data->set.httpversion == CURL_HTTP_VERSION_3) ||
     (conn->httpversion == 30))
    return "3";
#endif

#ifdef USE_NGHTTP2
  if(conn->proto.httpc.h2)
    return "2";
#endif

  if(use_http_1_1plus(data, conn))
    return "1.1";

  return "1.0";
}