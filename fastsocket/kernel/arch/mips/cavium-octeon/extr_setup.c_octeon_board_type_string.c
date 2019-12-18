#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  board_type; } ;

/* Variables and functions */
 char* cvmx_board_type_to_string (int /*<<< orphan*/ ) ; 
 TYPE_1__* octeon_bootinfo ; 
 char* octeon_model_get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_c0_prid () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

const char *octeon_board_type_string(void)
{
	static char name[80];
	sprintf(name, "%s (%s)",
		cvmx_board_type_to_string(octeon_bootinfo->board_type),
		octeon_model_get_string(read_c0_prid()));
	return name;
}