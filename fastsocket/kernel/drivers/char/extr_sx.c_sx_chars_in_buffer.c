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
struct sx_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  hi_txipos ; 
 int /*<<< orphan*/  hi_txopos ; 
 int sx_read_channel_byte (struct sx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sx_chars_in_buffer(void *ptr)
{
	struct sx_port *port = ptr;
	func_enter2();

	func_exit();
	return ((sx_read_channel_byte(port, hi_txipos) -
		 sx_read_channel_byte(port, hi_txopos)) & 0xff);
}