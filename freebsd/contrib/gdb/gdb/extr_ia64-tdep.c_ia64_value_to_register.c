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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  builtin_type_ia64_ext ; 
 int /*<<< orphan*/  convert_typed_floating (void const*,struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char*) ; 

__attribute__((used)) static void
ia64_value_to_register (struct frame_info *frame, int regnum,
                         struct type *valtype, const void *in)
{
  char out[MAX_REGISTER_SIZE];
  convert_typed_floating (in, valtype, out, builtin_type_ia64_ext);
  put_frame_register (frame, regnum, out);
}