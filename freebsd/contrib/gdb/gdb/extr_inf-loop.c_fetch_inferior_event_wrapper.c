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
 int /*<<< orphan*/  fetch_inferior_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
fetch_inferior_event_wrapper (gdb_client_data client_data)
{
  fetch_inferior_event (client_data);
  return 1;
}