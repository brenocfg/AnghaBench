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
struct connectdata {TYPE_1__* handler; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  statusline ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int CURLPROTO_RTSP ; 
 int /*<<< orphan*/  checkhttpprefix (struct Curl_easy*,char const*,size_t) ; 
 int /*<<< orphan*/  checkrtspprefix (struct Curl_easy*,char const*,size_t) ; 

__attribute__((used)) static statusline
checkprotoprefix(struct Curl_easy *data, struct connectdata *conn,
                 const char *s, size_t len)
{
#ifndef CURL_DISABLE_RTSP
  if(conn->handler->protocol & CURLPROTO_RTSP)
    return checkrtspprefix(data, s, len);
#else
  (void)conn;
#endif /* CURL_DISABLE_RTSP */

  return checkhttpprefix(data, s, len);
}