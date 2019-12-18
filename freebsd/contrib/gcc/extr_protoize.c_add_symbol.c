#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * fip; int /*<<< orphan*/ * ddip; int /*<<< orphan*/  symbol; int /*<<< orphan*/ * hash_next; } ;
typedef  TYPE_1__ hash_table_entry ;

/* Variables and functions */
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static hash_table_entry *
add_symbol (hash_table_entry *p, const char *s)
{
  p->hash_next = NULL;
  p->symbol = xstrdup (s);
  p->ddip = NULL;
  p->fip = NULL;
  return p;
}