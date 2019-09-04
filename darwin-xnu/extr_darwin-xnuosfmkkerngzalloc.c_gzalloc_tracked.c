#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ elem_size; scalar_t__ gzalloc_exempt; } ;

/* Variables and functions */
 scalar_t__ gzalloc_max ; 
 scalar_t__ gzalloc_min ; 
 scalar_t__ gzalloc_mode ; 
 TYPE_1__* gztrackzone ; 

__attribute__((used)) static inline boolean_t gzalloc_tracked(zone_t z) {
	return (gzalloc_mode &&
	    (((z->elem_size >= gzalloc_min) && (z->elem_size <= gzalloc_max)) || (z == gztrackzone)) &&
	    (z->gzalloc_exempt == 0));
}