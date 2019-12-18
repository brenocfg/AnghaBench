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

/* Variables and functions */
 long get_memory_packet_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_write_packet_config ; 

__attribute__((used)) static long
get_memory_write_packet_size (void)
{
  return get_memory_packet_size (&memory_write_packet_config);
}