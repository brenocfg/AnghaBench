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
struct csrow_info {int /*<<< orphan*/  nr_pages; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PAGES_TO_MiB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t csrow_size_show(struct csrow_info *csrow, char *data,
				int private)
{
	return sprintf(data, "%u\n", PAGES_TO_MiB(csrow->nr_pages));
}