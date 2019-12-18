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
struct pr_handle {unsigned int indent; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
indent (struct pr_handle *info)
{
  unsigned int i;

  for (i = 0; i < info->indent; i++)
    putc (' ', info->f);
}