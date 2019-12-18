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
struct gserial {int dummy; } ;
struct f_acm {int serial_state; } ;

/* Variables and functions */
 int ACM_CTRL_DCD ; 
 int ACM_CTRL_DSR ; 
 int /*<<< orphan*/  acm_notify_serial_state (struct f_acm*) ; 
 struct f_acm* port_to_acm (struct gserial*) ; 

__attribute__((used)) static void acm_disconnect(struct gserial *port)
{
	struct f_acm		*acm = port_to_acm(port);

	acm->serial_state &= ~(ACM_CTRL_DSR | ACM_CTRL_DCD);
	acm_notify_serial_state(acm);
}