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
struct type {int dummy; } ;
struct TYPE_2__ {int (* baseclass_offset ) (struct type*,int,char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 TYPE_1__ current_cp_abi ; 
 int /*<<< orphan*/  error (char*) ; 
 int stub1 (struct type*,int,char*,int /*<<< orphan*/ ) ; 

int
baseclass_offset (struct type *type, int index, char *valaddr,
		  CORE_ADDR address)
{
  if (current_cp_abi.baseclass_offset == NULL)
    error ("ABI doesn't define required function baseclass_offset");
  return (*current_cp_abi.baseclass_offset) (type, index, valaddr, address);
}