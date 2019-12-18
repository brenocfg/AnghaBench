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
struct connectdata {int httpversion; TYPE_1__* handler; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int CURLPROTO_SCP ; 
 int CURLPROTO_SFTP ; 
 scalar_t__ Curl_ssl_data_pending (struct connectdata const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 int PROTO_FAMILY_HTTP ; 

__attribute__((used)) static int data_pending(const struct connectdata *conn)
{
  /* in the case of libssh2, we can never be really sure that we have emptied
     its internal buffers so we MUST always try until we get EAGAIN back */
  return conn->handler->protocol&(CURLPROTO_SCP|CURLPROTO_SFTP) ||
#if defined(USE_NGHTTP2)
    Curl_ssl_data_pending(conn, FIRSTSOCKET) ||
    /* For HTTP/2, we may read up everything including response body
       with header fields in Curl_http_readwrite_headers. If no
       content-length is provided, curl waits for the connection
       close, which we emulate it using conn->proto.httpc.closed =
       TRUE. The thing is if we read everything, then http2_recv won't
       be called and we cannot signal the HTTP/2 stream has closed. As
       a workaround, we return nonzero here to call http2_recv. */
    ((conn->handler->protocol&PROTO_FAMILY_HTTP) && conn->httpversion >= 20);
#else
    Curl_ssl_data_pending(conn, FIRSTSOCKET);
#endif
}