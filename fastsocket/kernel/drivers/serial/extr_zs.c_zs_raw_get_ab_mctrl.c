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
typedef  int u8 ;
struct zs_port {int dummy; } ;

/* Variables and functions */
 int CTS ; 
 int DCD ; 
 int /*<<< orphan*/  R0 ; 
 int SYNC_HUNT ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int zs_raw_get_ab_mctrl(struct zs_port *zport_a,
					struct zs_port *zport_b)
{
	u8 status_a, status_b;
	unsigned int mctrl;

	status_a = read_zsreg(zport_a, R0);
	status_b = read_zsreg(zport_b, R0);

	mctrl = ((status_b & CTS) ? TIOCM_CTS : 0) |
		((status_b & DCD) ? TIOCM_CAR : 0) |
		((status_a & DCD) ? TIOCM_RNG : 0) |
		((status_a & SYNC_HUNT) ? TIOCM_DSR : 0);

	return mctrl;
}