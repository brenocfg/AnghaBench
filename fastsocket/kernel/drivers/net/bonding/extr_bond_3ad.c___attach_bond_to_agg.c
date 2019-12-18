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
struct port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void __attach_bond_to_agg(struct port *port)
{
	port=NULL; // just to satisfy the compiler
	// This function does nothing since the parser/multiplexer of the receive
	// and the parser/multiplexer of the aggregator are already combined
}