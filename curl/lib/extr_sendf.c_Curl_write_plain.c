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
struct connectdata {scalar_t__* sock; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_send_plain (struct connectdata*,int,void const*,size_t,int /*<<< orphan*/ *) ; 
 size_t SECONDARYSOCKET ; 

CURLcode Curl_write_plain(struct connectdata *conn,
                          curl_socket_t sockfd,
                          const void *mem,
                          size_t len,
                          ssize_t *written)
{
  ssize_t bytes_written;
  CURLcode result;
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  bytes_written = Curl_send_plain(conn, num, mem, len, &result);

  *written = bytes_written;

  return result;
}