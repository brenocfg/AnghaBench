#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values_list_t ;
struct TYPE_3__ {void* value; } ;
typedef  TYPE_1__ value_entry_t ;
typedef  int /*<<< orphan*/  pthread_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_TLS_INDEX ; 
 TYPE_1__* find_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pvTaskGetThreadLocalStoragePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *pthread_getspecific(pthread_key_t key)
{
    values_list_t *tls = (values_list_t *) pvTaskGetThreadLocalStoragePointer(NULL, PTHREAD_TLS_INDEX);
    if (tls == NULL) {
        return NULL;
    }

    value_entry_t *entry = find_value(tls, key);
    if(entry != NULL) {
        return entry->value;
    }
    return NULL;
}