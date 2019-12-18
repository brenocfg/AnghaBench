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
 void* dep_map ; 
 void* ghb_resource_get (char*) ; 
 void* rev_map ; 

void
ghb_init_dep_map()
{
    dep_map = ghb_resource_get("widget-deps");
    rev_map = ghb_resource_get("widget-reverse-deps");
}