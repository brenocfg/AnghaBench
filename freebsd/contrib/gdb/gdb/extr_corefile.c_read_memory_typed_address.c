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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_typed_address (char*,struct type*) ; 
 int /*<<< orphan*/  read_memory (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

CORE_ADDR
read_memory_typed_address (CORE_ADDR addr, struct type *type)
{
  char *buf = alloca (TYPE_LENGTH (type));
  read_memory (addr, buf, TYPE_LENGTH (type));
  return extract_typed_address (buf, type);
}