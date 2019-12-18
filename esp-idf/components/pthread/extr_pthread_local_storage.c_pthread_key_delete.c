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
typedef  int /*<<< orphan*/  pthread_key_t ;
typedef  int /*<<< orphan*/  key_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_entry_t_ ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_keys ; 
 int /*<<< orphan*/  s_keys_lock ; 

int pthread_key_delete(pthread_key_t key)
{

    portENTER_CRITICAL(&s_keys_lock);

    /* Ideally, we would also walk all tasks' thread local storage value_list here
       and delete any values associated with this key. We do not do this...
    */

    key_entry_t *entry = find_key(key);
    if (entry != NULL) {
        SLIST_REMOVE(&s_keys, entry, key_entry_t_, next);
        free(entry);
    }

    portEXIT_CRITICAL(&s_keys_lock);

    return 0;
}