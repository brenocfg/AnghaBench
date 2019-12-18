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
struct TYPE_2__ {int /*<<< orphan*/ * tcpconnect; } ;
struct connectdata {scalar_t__* sock; TYPE_1__ bits; } ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_closesocket (struct connectdata*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t SECONDARYSOCKET ; 

__attribute__((used)) static void close_secondarysocket(struct connectdata *conn)
{
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET]) {
    Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
    conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
  }
  conn->bits.tcpconnect[SECONDARYSOCKET] = FALSE;
}