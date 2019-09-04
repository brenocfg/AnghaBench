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
typedef  int access_t ;

/* Variables and functions */
 int TYPE_FREE ; 
 int TYPE_READ ; 
 int TYPE_WRITE ; 

__attribute__((used)) static const char *
access_str(access_t type)
{
	if (type & TYPE_READ) {
		return "load from";
	} else if (type & TYPE_WRITE) {
		return "store to";
	} else if (type & TYPE_FREE) {
		return "free of";
	} else {
		return "access of";
	}
}