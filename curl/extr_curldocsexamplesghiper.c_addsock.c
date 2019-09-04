#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_9__ {int /*<<< orphan*/  multi; } ;
struct TYPE_8__ {int /*<<< orphan*/  ch; TYPE_2__* global; } ;
typedef  TYPE_1__ SockInfo ;
typedef  TYPE_2__ GlobalInfo ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  curl_multi_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_io_channel_unix_new (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  setsock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static void addsock(curl_socket_t s, CURL *easy, int action, GlobalInfo *g)
{
  SockInfo *fdp = g_malloc0(sizeof(SockInfo));

  fdp->global = g;
  fdp->ch = g_io_channel_unix_new(s);
  setsock(fdp, s, easy, action, g);
  curl_multi_assign(g->multi, s, fdp);
}