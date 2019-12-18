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
struct zs_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0 ; 
 int Rx_CH_AV ; 
 int /*<<< orphan*/  read_zsdata (struct zs_port*) ; 
 int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zs_receive_drain(struct zs_port *zport)
{
	int loops = 10000;

	while ((read_zsreg(zport, R0) & Rx_CH_AV) && --loops)
		read_zsdata(zport);
	return loops;
}