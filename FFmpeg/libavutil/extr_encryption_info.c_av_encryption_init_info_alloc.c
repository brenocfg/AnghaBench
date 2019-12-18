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
struct TYPE_4__ {size_t system_id_size; size_t num_key_ids; size_t key_id_size; size_t data_size; void** key_ids; void* data; void* system_id; } ;
typedef  TYPE_1__ AVEncryptionInitInfo ;

/* Variables and functions */
 int /*<<< orphan*/  av_encryption_init_info_free (TYPE_1__*) ; 
 void* av_mallocz (size_t) ; 
 void** av_mallocz_array (size_t,int) ; 

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_size, uint32_t num_key_ids, uint32_t key_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    info = av_mallocz(sizeof(*info));
    if (!info)
        return NULL;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->key_ids = key_id_size ? av_mallocz_array(num_key_ids, sizeof(*info->key_ids)) : NULL;
    info->num_key_ids = num_key_ids;
    info->key_id_size = key_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    if ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->key_ids && num_key_ids && key_id_size)) {
        av_encryption_init_info_free(info);
        return NULL;
    }

    if (key_id_size) {
        for (i = 0; i < num_key_ids; i++) {
            info->key_ids[i] = av_mallocz(key_id_size);
            if (!info->key_ids[i]) {
                av_encryption_init_info_free(info);
                return NULL;
            }
        }
    }

    return info;
}