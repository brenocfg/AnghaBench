#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct Curl_easy {int mstate; TYPE_1__* conn; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_8__ {struct Curl_easy* data; } ;

/* Variables and functions */
#define  CURLM_STATE_COMPLETED 145 
#define  CURLM_STATE_CONNECT 144 
#define  CURLM_STATE_DO 143 
#define  CURLM_STATE_DOING 142 
#define  CURLM_STATE_DONE 141 
#define  CURLM_STATE_DO_DONE 140 
#define  CURLM_STATE_DO_MORE 139 
#define  CURLM_STATE_INIT 138 
#define  CURLM_STATE_LAST 137 
#define  CURLM_STATE_MSGSENT 136 
#define  CURLM_STATE_PERFORM 135 
#define  CURLM_STATE_PROTOCONNECT 134 
#define  CURLM_STATE_SENDPROTOCONNECT 133 
#define  CURLM_STATE_TOOFAST 132 
#define  CURLM_STATE_WAITCONNECT 131 
#define  CURLM_STATE_WAITDO 130 
#define  CURLM_STATE_WAITPROXYCONNECT 129 
#define  CURLM_STATE_WAITRESOLVE 128 
 int Curl_resolv_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int Curl_single_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int doing_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int domore_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int protocol_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int waitconnect_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int waitproxyconnect_getsock (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multi_getsock(struct Curl_easy *data,
                         curl_socket_t *socks)
{
  /* The no connection case can happen when this is called from
     curl_multi_remove_handle() => singlesocket() => multi_getsock().
  */
  if(!data->conn)
    return 0;

  if(data->mstate > CURLM_STATE_CONNECT &&
     data->mstate < CURLM_STATE_COMPLETED) {
    /* Set up ownership correctly */
    data->conn->data = data;
  }

  switch(data->mstate) {
  default:
#if 0 /* switch back on these cases to get the compiler to check for all enums
         to be present */
  case CURLM_STATE_TOOFAST:  /* returns 0, so will not select. */
  case CURLM_STATE_COMPLETED:
  case CURLM_STATE_MSGSENT:
  case CURLM_STATE_INIT:
  case CURLM_STATE_CONNECT:
  case CURLM_STATE_WAITDO:
  case CURLM_STATE_DONE:
  case CURLM_STATE_LAST:
    /* this will get called with CURLM_STATE_COMPLETED when a handle is
       removed */
#endif
    return 0;

  case CURLM_STATE_WAITRESOLVE:
    return Curl_resolv_getsock(data->conn, socks);

  case CURLM_STATE_PROTOCONNECT:
  case CURLM_STATE_SENDPROTOCONNECT:
    return protocol_getsock(data->conn, socks);

  case CURLM_STATE_DO:
  case CURLM_STATE_DOING:
    return doing_getsock(data->conn, socks);

  case CURLM_STATE_WAITPROXYCONNECT:
    return waitproxyconnect_getsock(data->conn, socks);

  case CURLM_STATE_WAITCONNECT:
    return waitconnect_getsock(data->conn, socks);

  case CURLM_STATE_DO_MORE:
    return domore_getsock(data->conn, socks);

  case CURLM_STATE_DO_DONE: /* since is set after DO is completed, we switch
                               to waiting for the same as the *PERFORM
                               states */
  case CURLM_STATE_PERFORM:
    return Curl_single_getsock(data->conn, socks);
  }

}