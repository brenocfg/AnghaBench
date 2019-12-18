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
struct specialix_port {int dummy; } ;

/* Variables and functions */
 int SX_PORT (struct specialix_port const*) ; 
 int sx_port ; 

__attribute__((used)) static inline int port_No(struct specialix_port const *port)
{
	return SX_PORT(port - sx_port);
}