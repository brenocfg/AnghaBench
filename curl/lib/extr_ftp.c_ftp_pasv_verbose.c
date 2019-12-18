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
struct connectdata {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Curl_addrinfo ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_printable_address (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,char*,char*,int) ; 

__attribute__((used)) static void
ftp_pasv_verbose(struct connectdata *conn,
                 Curl_addrinfo *ai,
                 char *newhost, /* ascii version */
                 int port)
{
  char buf[256];
  Curl_printable_address(ai, buf, sizeof(buf));
  infof(conn->data, "Connecting to %s (%s) port %d\n", newhost, buf, port);
}