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
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  extract_signed_integer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_signed_integer (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_long (struct type*,void*) ; 

__attribute__((used)) static CORE_ADDR
mips_integer_to_address (struct type *type, void *buf)
{
  char *tmp = alloca (TYPE_LENGTH (builtin_type_void_data_ptr));
  LONGEST val = unpack_long (type, buf);
  store_signed_integer (tmp, TYPE_LENGTH (builtin_type_void_data_ptr), val);
  return extract_signed_integer (tmp,
				 TYPE_LENGTH (builtin_type_void_data_ptr));
}