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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool called_as_built_in (tree node)
{
  const char *name = IDENTIFIER_POINTER (DECL_NAME (node));
  if (strncmp (name, "__builtin_", 10) == 0)
    return true;
  if (strncmp (name, "__sync_", 7) == 0)
    return true;
  return false;
}