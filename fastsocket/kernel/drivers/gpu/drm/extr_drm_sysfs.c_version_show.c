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
struct class {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* CORE_DATE ; 
 int CORE_MAJOR ; 
 int CORE_MINOR ; 
 char* CORE_NAME ; 
 int CORE_PATCHLEVEL ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int,char*) ; 

__attribute__((used)) static ssize_t version_show(struct class *dev, char *buf)
{
	return sprintf(buf, "%s %d.%d.%d %s\n", CORE_NAME, CORE_MAJOR,
		       CORE_MINOR, CORE_PATCHLEVEL, CORE_DATE);
}