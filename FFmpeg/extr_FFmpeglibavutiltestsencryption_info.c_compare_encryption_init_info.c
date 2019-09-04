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
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__ system_id_size; scalar_t__ num_key_ids; scalar_t__ key_id_size; scalar_t__ data_size; struct TYPE_4__* next; int /*<<< orphan*/ * key_ids; int /*<<< orphan*/  data; int /*<<< orphan*/  system_id; } ;
typedef  TYPE_1__ AVEncryptionInitInfo ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int compare_encryption_init_info(const AVEncryptionInitInfo *a, const AVEncryptionInitInfo *b) {
    if (!a || !b || a->system_id_size != b->system_id_size ||
        a->num_key_ids != b->num_key_ids || a->key_id_size != b->key_id_size ||
        a->data_size != b->data_size)
        return 1;

    if (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        return 1;

    for (uint32_t i = 0; i < a->num_key_ids; i++) {
        if (memcmp(a->key_ids[i], b->key_ids[i], a->key_id_size) != 0)
            return 1;
    }

    if (a->next || b->next) {
        if (!a->next || !b->next)
            return 1;
        if (compare_encryption_init_info(a->next, b->next) != 0)
            return 1;
    }

    return 0;
}