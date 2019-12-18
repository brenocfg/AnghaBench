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
struct csrow_info {size_t dtype; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** dev_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t csrow_dev_type_show(struct csrow_info *csrow, char *data,
				int private)
{
	return sprintf(data, "%s\n", dev_types[csrow->dtype]);
}