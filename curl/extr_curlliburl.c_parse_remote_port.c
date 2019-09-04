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
struct connectdata {unsigned short remote_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  uh; scalar_t__ allow_port; } ;
struct TYPE_4__ {scalar_t__ use_port; } ;
struct Curl_easy {TYPE_1__ state; TYPE_2__ set; } ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  scalar_t__ CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLUPART_PORT ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,unsigned short) ; 

__attribute__((used)) static CURLcode parse_remote_port(struct Curl_easy *data,
                                  struct connectdata *conn)
{

  if(data->set.use_port && data->state.allow_port) {
    /* if set, we use this instead of the port possibly given in the URL */
    char portbuf[16];
    CURLUcode uc;
    conn->remote_port = (unsigned short)data->set.use_port;
    msnprintf(portbuf, sizeof(portbuf), "%d", conn->remote_port);
    uc = curl_url_set(data->state.uh, CURLUPART_PORT, portbuf, 0);
    if(uc)
      return CURLE_OUT_OF_MEMORY;
  }

  return CURLE_OK;
}