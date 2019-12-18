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
struct comedi_lrange {int dummy; } ;

/* Variables and functions */
 struct comedi_lrange const** ao_range_table ; 

__attribute__((used)) static const struct comedi_lrange *opt_ao_range_lkup(int x)
{
	if (x < 0 || x >= 5)
		x = 0;
	return ao_range_table[x];
}