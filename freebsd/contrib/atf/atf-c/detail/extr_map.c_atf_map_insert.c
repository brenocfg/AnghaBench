#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct map_entry {int m_managed; void* m_value; int /*<<< orphan*/  m_key; } ;
struct TYPE_8__ {int /*<<< orphan*/  m_list; } ;
typedef  TYPE_1__ atf_map_t ;
struct TYPE_9__ {struct map_entry* m_entry; } ;
typedef  TYPE_2__ atf_map_iter_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 scalar_t__ atf_equal_map_iter_map_iter (TYPE_2__,int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_append (int /*<<< orphan*/ *,struct map_entry*,int) ; 
 int /*<<< orphan*/  atf_map_end (TYPE_1__*) ; 
 TYPE_2__ atf_map_find (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 int /*<<< orphan*/  free (void*) ; 
 struct map_entry* new_entry (char const*,void*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

atf_error_t
atf_map_insert(atf_map_t *m, const char *key, void *value, bool managed)
{
    struct map_entry *me;
    atf_error_t err;
    atf_map_iter_t iter;

    iter = atf_map_find(m, key);
    if (atf_equal_map_iter_map_iter(iter, atf_map_end(m))) {
        me = new_entry(key, value, managed);
        if (me == NULL)
            err = atf_no_memory_error();
        else {
            err = atf_list_append(&m->m_list, me, false);
            if (atf_is_error(err)) {
                if (managed)
                    free(value);
            }
        }
    } else {
        me = iter.m_entry;
        if (me->m_managed)
            free(me->m_value);

        INV(strcmp(me->m_key, key) == 0);
        me->m_value = value;
        me->m_managed = managed;

        err = atf_no_error();
    }

    return err;
}