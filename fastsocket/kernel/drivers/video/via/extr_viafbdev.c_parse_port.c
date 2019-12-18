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
 int INTERFACE_DFP ; 
 int INTERFACE_DFP_HIGH ; 
 int INTERFACE_DFP_LOW ; 
 int INTERFACE_DVP0 ; 
 int INTERFACE_DVP1 ; 
 int INTERFACE_NONE ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int parse_port(char *opt_str, int *output_interface)
{
	if (!strncmp(opt_str, "DVP0", 4))
		*output_interface = INTERFACE_DVP0;
	else if (!strncmp(opt_str, "DVP1", 4))
		*output_interface = INTERFACE_DVP1;
	else if (!strncmp(opt_str, "DFP_HIGHLOW", 11))
		*output_interface = INTERFACE_DFP;
	else if (!strncmp(opt_str, "DFP_HIGH", 8))
		*output_interface = INTERFACE_DFP_HIGH;
	else if (!strncmp(opt_str, "DFP_LOW", 7))
		*output_interface = INTERFACE_DFP_LOW;
	else
		*output_interface = INTERFACE_NONE;
	return 0;
}