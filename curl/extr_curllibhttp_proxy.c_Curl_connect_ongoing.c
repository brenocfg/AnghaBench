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
struct connectdata {TYPE_1__* connect_state; } ;
struct TYPE_2__ {scalar_t__ tunnel_state; } ;

/* Variables and functions */
 scalar_t__ TUNNEL_COMPLETE ; 

bool Curl_connect_ongoing(struct connectdata *conn)
{
  return conn->connect_state &&
    (conn->connect_state->tunnel_state != TUNNEL_COMPLETE);
}