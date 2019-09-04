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
struct http_connect_state {int /*<<< orphan*/  tunnel_state; } ;
struct connectdata {int /*<<< orphan*/  data; struct http_connect_state* connect_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNNEL_COMPLETE ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void connect_done(struct connectdata *conn)
{
  struct http_connect_state *s = conn->connect_state;
  s->tunnel_state = TUNNEL_COMPLETE;
  infof(conn->data, "CONNECT phase completed!\n");
}