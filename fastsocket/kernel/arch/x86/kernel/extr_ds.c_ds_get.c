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
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;
typedef  enum ds_field { ____Placeholder_ds_field } ds_field ;
struct TYPE_2__ {int sizeof_ptr_field; } ;

/* Variables and functions */
 TYPE_1__ ds_cfg ; 

__attribute__((used)) static inline unsigned long
ds_get(const unsigned char *base, enum ds_qualifier qual, enum ds_field field)
{
	base += (ds_cfg.sizeof_ptr_field * (field + (4 * qual)));
	return *(unsigned long *)base;
}