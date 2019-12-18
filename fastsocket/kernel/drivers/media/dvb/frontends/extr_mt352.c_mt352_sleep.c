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
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  mt352_softdown ;

/* Variables and functions */
#define  CLOCK_CTL 128 
 int /*<<< orphan*/  _mt352_write (struct dvb_frontend*,int*,int) ; 

__attribute__((used)) static int mt352_sleep(struct dvb_frontend* fe)
{
	static u8 mt352_softdown[] = { CLOCK_CTL, 0x20, 0x08 };

	_mt352_write(fe, mt352_softdown, sizeof(mt352_softdown));
	return 0;
}