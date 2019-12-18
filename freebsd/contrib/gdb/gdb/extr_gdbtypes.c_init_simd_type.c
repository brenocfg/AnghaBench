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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  append_composite_type_field (struct type*,char*,struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* create_array_type (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_range_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct type* init_composite_type (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
init_simd_type (char *name,
		struct type *elt_type,
		char *elt_name,
		int n)
{
  struct type *simd_type;
  struct type *array_type;
  
  simd_type = init_composite_type (name, TYPE_CODE_STRUCT);
  array_type = create_array_type (0, elt_type,
				  create_range_type (0, builtin_type_int,
						     0, n-1));
  append_composite_type_field (simd_type, elt_name, array_type);
  return simd_type;
}