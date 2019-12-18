#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hso_shared_int {int dummy; } ;
struct hso_serial {struct hso_shared_int* shared_int; } ;
struct TYPE_3__ {int port_spec; } ;

/* Variables and functions */
 int HSO_PORT_MASK ; 
 int HSO_SERIAL_TTY_MINORS ; 
 struct hso_serial* dev2ser (TYPE_1__*) ; 
 int hso_mux_to_port (int) ; 
 TYPE_1__** serial_table ; 

__attribute__((used)) static struct hso_serial *get_serial_by_shared_int_and_type(
					struct hso_shared_int *shared_int,
					int mux)
{
	int i, port;

	port = hso_mux_to_port(mux);

	for (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) {
		if (serial_table[i]
		    && (dev2ser(serial_table[i])->shared_int == shared_int)
		    && ((serial_table[i]->port_spec & HSO_PORT_MASK) == port)) {
			return dev2ser(serial_table[i]);
		}
	}

	return NULL;
}