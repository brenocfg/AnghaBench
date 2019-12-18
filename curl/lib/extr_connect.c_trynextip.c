#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {scalar_t__* tempsock; TYPE_1__** tempaddr; } ;
typedef  scalar_t__ curl_socket_t ;
struct TYPE_3__ {int ai_family; struct TYPE_3__* ai_next; } ;
typedef  TYPE_1__ Curl_addrinfo ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 scalar_t__ CURLE_COULDNT_CONNECT ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_closesocket (struct connectdata*,scalar_t__) ; 
 int FIRSTSOCKET ; 
 scalar_t__ singleipconnect (struct connectdata*,TYPE_1__*,int) ; 

__attribute__((used)) static CURLcode trynextip(struct connectdata *conn,
                          int sockindex,
                          int tempindex)
{
  const int other = tempindex ^ 1;
  CURLcode result = CURLE_COULDNT_CONNECT;

  /* First clean up after the failed socket.
     Don't close it yet to ensure that the next IP's socket gets a different
     file descriptor, which can prevent bugs when the curl_multi_socket_action
     interface is used with certain select() replacements such as kqueue. */
  curl_socket_t fd_to_close = conn->tempsock[tempindex];
  conn->tempsock[tempindex] = CURL_SOCKET_BAD;

  if(sockindex == FIRSTSOCKET) {
    Curl_addrinfo *ai = NULL;
    int family = AF_UNSPEC;

    if(conn->tempaddr[tempindex]) {
      /* find next address in the same protocol family */
      family = conn->tempaddr[tempindex]->ai_family;
      ai = conn->tempaddr[tempindex]->ai_next;
    }
#ifdef ENABLE_IPV6
    else if(conn->tempaddr[0]) {
      /* happy eyeballs - try the other protocol family */
      int firstfamily = conn->tempaddr[0]->ai_family;
      family = (firstfamily == AF_INET) ? AF_INET6 : AF_INET;
      ai = conn->tempaddr[0]->ai_next;
    }
#endif

    while(ai) {
      if(conn->tempaddr[other]) {
        /* we can safely skip addresses of the other protocol family */
        while(ai && ai->ai_family != family)
          ai = ai->ai_next;
      }

      if(ai) {
        result = singleipconnect(conn, ai, tempindex);
        if(result == CURLE_COULDNT_CONNECT) {
          ai = ai->ai_next;
          continue;
        }

        conn->tempaddr[tempindex] = ai;
      }
      break;
    }
  }

  if(fd_to_close != CURL_SOCKET_BAD)
    Curl_closesocket(conn, fd_to_close);

  return result;
}