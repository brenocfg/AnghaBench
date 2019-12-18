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
struct ni_65xx_board {int num_dio_ports; int num_di_ports; int num_do_ports; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned ni_65xx_total_num_ports(const struct ni_65xx_board
					       *board)
{
	return board->num_dio_ports + board->num_di_ports + board->num_do_ports;
}