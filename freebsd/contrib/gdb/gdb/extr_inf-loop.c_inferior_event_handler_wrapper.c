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
typedef  int /*<<< orphan*/  gdb_client_data ;

/* Variables and functions */
 int /*<<< orphan*/  INF_QUIT_REQ ; 
 int /*<<< orphan*/  inferior_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
inferior_event_handler_wrapper (gdb_client_data client_data)
{
  inferior_event_handler (INF_QUIT_REQ, client_data);
}