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
struct bfad_port_s {int dummy; } ;
struct bfa_fcs_lport_s {struct bfad_port_s* bfad_port; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bfad_port_s *
bfa_fcs_lport_get_drvport(struct bfa_fcs_lport_s *port)
{
	return port->bfad_port;
}