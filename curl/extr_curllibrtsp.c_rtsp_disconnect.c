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
struct TYPE_3__ {int /*<<< orphan*/  rtp_buf; } ;
struct TYPE_4__ {TYPE_1__ rtspc; } ;
struct connectdata {TYPE_2__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode rtsp_disconnect(struct connectdata *conn, bool dead)
{
  (void) dead;
  Curl_safefree(conn->proto.rtspc.rtp_buf);
  return CURLE_OK;
}