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

/* Variables and functions */
#define  EB 131 
#define  ER 130 
#define  IB 129 
#define  IR 128 

__attribute__((used)) static const char *
qfq_state2str(int s)
{
	const char *c;

	switch (s) {
	case ER:
		c = "ER";
		break;
	case IR:
		c = "IR";
		break;
	case EB:
		c = "EB";
		break;
	case IB:
		c = "IB";
		break;
	default:
		c = "?";
		break;
	}
	return (c);
}