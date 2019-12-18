#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int pthread_key_t ;
typedef  int /*<<< orphan*/  pthread_destructor_t ;
struct TYPE_5__ {int key; int /*<<< orphan*/  destructor; } ;
typedef  TYPE_1__ key_entry_t ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_keys ; 
 int /*<<< orphan*/  s_keys_lock ; 

int pthread_key_create(pthread_key_t *key, pthread_destructor_t destructor)
{
    key_entry_t *new_key = malloc(sizeof(key_entry_t));
    if (new_key == NULL) {
        return ENOMEM;
    }

    portENTER_CRITICAL(&s_keys_lock);

    const key_entry_t *head = SLIST_FIRST(&s_keys);
    new_key->key = (head == NULL) ? 1 : (head->key + 1);
    new_key->destructor = destructor;
    *key = new_key->key;

    SLIST_INSERT_HEAD(&s_keys, new_key, next);

    portEXIT_CRITICAL(&s_keys_lock);
    return 0;
}