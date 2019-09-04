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
struct Curl_easy {int dummy; } ;

/* Variables and functions */
 scalar_t__ use_http_1_1plus (struct Curl_easy const*,struct connectdata const*) ; 

__attribute__((used)) static const char *get_http_string(const struct Curl_easy *data,
                                   const struct connectdata *conn)
{
#ifdef USE_NGHTTP2
  if(conn->proto.httpc.h2)
    return "2";
#endif

  if(use_http_1_1plus(data, conn))
    return "1.1";

  return "1.0";
}