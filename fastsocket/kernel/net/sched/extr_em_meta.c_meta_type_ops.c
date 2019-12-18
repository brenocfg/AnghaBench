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
struct meta_value {int dummy; } ;
struct meta_type_ops {int dummy; } ;

/* Variables and functions */
 struct meta_type_ops* __meta_type_ops ; 
 size_t meta_type (struct meta_value*) ; 

__attribute__((used)) static inline struct meta_type_ops * meta_type_ops(struct meta_value *v)
{
	return &__meta_type_ops[meta_type(v)];
}