#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {TYPE_2__* data; int /*<<< orphan*/ * sock; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int os_errno; } ;
struct TYPE_4__ {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_AGAIN ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  Curl_strerror (int,char*,int) ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 int EINTR ; 
 int EWOULDBLOCK ; 
 int SOCKERRNO ; 
 int STRERROR_LEN ; 
 int /*<<< orphan*/  failf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_receive_plain (struct connectdata*,int) ; 
 int swrite (int /*<<< orphan*/ ,void const*,size_t) ; 

ssize_t Curl_send_plain(struct connectdata *conn, int num,
                        const void *mem, size_t len, CURLcode *code)
{
  curl_socket_t sockfd = conn->sock[num];
  ssize_t bytes_written;
  /* WinSock will destroy unread received data if send() is
     failed.
     To avoid lossage of received data, recv() must be
     performed before every send() if any incoming data is
     available. */
  pre_receive_plain(conn, num);

#if defined(MSG_FASTOPEN) && !defined(TCP_FASTOPEN_CONNECT) /* Linux */
  if(conn->bits.tcp_fastopen) {
    bytes_written = sendto(sockfd, mem, len, MSG_FASTOPEN,
                           conn->ip_addr->ai_addr, conn->ip_addr->ai_addrlen);
    conn->bits.tcp_fastopen = FALSE;
  }
  else
#endif
    bytes_written = swrite(sockfd, mem, len);

  *code = CURLE_OK;
  if(-1 == bytes_written) {
    int err = SOCKERRNO;

    if(
#ifdef WSAEWOULDBLOCK
      /* This is how Windows does it */
      (WSAEWOULDBLOCK == err)
#else
      /* errno may be EWOULDBLOCK or on some systems EAGAIN when it returned
         due to its inability to send off data without blocking. We therefore
         treat both error codes the same here */
      (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err) ||
      (EINPROGRESS == err)
#endif
      ) {
      /* this is just a case of EWOULDBLOCK */
      bytes_written = 0;
      *code = CURLE_AGAIN;
    }
    else {
      char buffer[STRERROR_LEN];
      failf(conn->data, "Send failure: %s",
            Curl_strerror(err, buffer, sizeof(buffer)));
      conn->data->state.os_errno = err;
      *code = CURLE_SEND_ERROR;
    }
  }
  return bytes_written;
}