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
struct list_entry {int m_managed; void* m_object; int /*<<< orphan*/ * m_next; int /*<<< orphan*/  m_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static
struct list_entry *
new_entry(void *object, bool managed)
{
    struct list_entry *le;

    le = (struct list_entry *)malloc(sizeof(*le));
    if (le != NULL) {
        le->m_prev = le->m_next = NULL;
        le->m_object = object;
        le->m_managed = managed;
    } else
        free(object);

    return le;
}