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
struct dynstring {int size; } ;

/* Variables and functions */
 int dynstring_set_size (struct dynstring*,int) ; 

__attribute__((used)) static int dynstring_grow(struct dynstring *ds)
{
   return dynstring_set_size(ds, (3*ds->size)/2);
}