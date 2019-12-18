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
 scalar_t__ DEPRECATED_STREQ (char*,char*) ; 
 char* ada_type_name (struct type*) ; 

__attribute__((used)) static int
is_nondebugging_type (struct type *type)
{
  char *name = ada_type_name (type);
  return (name != NULL && DEPRECATED_STREQ (name, "<variable, no debug info>"));
}