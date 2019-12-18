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
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_STATE_SCANNING ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  h_queue ; 
 int /*<<< orphan*/  hb_scan (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ hb_status ; 

void
ghb_backend_queue_scan(const gchar *path, gint titlenum)
{
    g_debug("ghb_backend_queue_scan()");
    hb_scan( h_queue, path, titlenum, -1, 0, 0 );
    hb_status.queue.state |= GHB_STATE_SCANNING;
}