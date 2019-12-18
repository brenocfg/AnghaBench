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
struct list_entry {struct list_entry* m_object; scalar_t__ m_managed; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct list_entry*) ; 

__attribute__((used)) static
void
delete_entry(struct list_entry *le)
{
    if (le->m_managed)
        free(le->m_object);

    free(le);
}