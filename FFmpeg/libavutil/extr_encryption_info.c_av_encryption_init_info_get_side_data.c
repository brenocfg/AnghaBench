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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/ * key_ids; int /*<<< orphan*/  system_id; struct TYPE_5__* next; } ;
typedef  TYPE_1__ AVEncryptionInitInfo ;

/* Variables and functions */
 scalar_t__ AV_RB32 (int /*<<< orphan*/  const*) ; 
 size_t FF_ENCRYPTION_INIT_INFO_EXTRA ; 
 TYPE_1__* av_encryption_init_info_alloc (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  av_encryption_init_info_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    const uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = NULL, *info, *temp_info;
    uint64_t system_id_size, num_key_ids, key_id_size, data_size, i, j;
    uint64_t init_info_count;

    if (!side_data || side_data_size < 4)
        return NULL;

    init_info_count = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    for (i = 0; i < init_info_count; i++) {
        if (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            return NULL;
        }

        system_id_size = AV_RB32(side_data);
        num_key_ids = AV_RB32(side_data + 4);
        key_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        if (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + num_key_ids * key_id_size) {
            av_encryption_init_info_free(ret);
            return NULL;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, num_key_ids, key_id_size, data_size);
        if (!temp_info) {
            av_encryption_init_info_free(ret);
            return NULL;
        }
        if (i == 0) {
            info = ret = temp_info;
        } else {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        for (j = 0; j < num_key_ids; j++) {
            memcpy(info->key_ids[j], side_data, key_id_size);
            side_data += key_id_size;
            side_data_size -= key_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    return ret;
}