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
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  IO_REG_FCTR ; 
 int /*<<< orphan*/  ioasic_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cycle_t dec_ioasic_hpt_read(struct clocksource *cs)
{
	return ioasic_read(IO_REG_FCTR);
}