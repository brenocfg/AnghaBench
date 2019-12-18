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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_ATTR_STRING (char const*) ; 
 int /*<<< orphan*/  EQ_ATTR ; 
 int /*<<< orphan*/  attr_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
attr_eq (const char *name, const char *value)
{
  return attr_rtx (EQ_ATTR, DEF_ATTR_STRING (name), DEF_ATTR_STRING (value));
}