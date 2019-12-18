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
typedef  enum ctor_kinds { ____Placeholder_ctor_kinds } ctor_kinds ;

/* Variables and functions */
 int complete_object_ctor ; 
 int /*<<< orphan*/  constructor_pattern ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ctor_kinds
hpacc_is_constructor_name (const char *name)
{
  if (regexec (&constructor_pattern, name, 0, 0, 0) == 0)
    return complete_object_ctor;
  else
    return 0;
}