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
 int /*<<< orphan*/  gdb_kod_display (char*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static void
bad_packet (void)
{
  (*gdb_kod_display) ("Remote target returned malformed packet.\n");
}