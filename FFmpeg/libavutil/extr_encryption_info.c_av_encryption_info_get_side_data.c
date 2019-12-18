#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
struct TYPE_6__ {TYPE_1__* subsamples; int /*<<< orphan*/  iv; int /*<<< orphan*/  key_id; void* skip_byte_block; void* crypt_byte_block; void* scheme; } ;
struct TYPE_5__ {void* bytes_of_protected_data; void* bytes_of_clear_data; } ;
typedef  TYPE_2__ AVEncryptionInfo ;

/* Variables and functions */
 void* AV_RB32 (int /*<<< orphan*/  const*) ; 
 size_t FF_ENCRYPTION_INFO_EXTRA ; 
 TYPE_2__* av_encryption_info_alloc (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

AVEncryptionInfo *av_encryption_info_get_side_data(const uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t key_id_size, iv_size, subsample_count, i;

    if (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        return NULL;

    key_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_count = AV_RB32(buffer + 20);

    if (size < FF_ENCRYPTION_INFO_EXTRA + key_id_size + iv_size + subsample_count * 8)
        return NULL;

    info = av_encryption_info_alloc(subsample_count, key_id_size, iv_size);
    if (!info)
        return NULL;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->key_id, buffer + 24, key_id_size);
    memcpy(info->iv, buffer + key_id_size + 24, iv_size);

    buffer += key_id_size + iv_size + 24;
    for (i = 0; i < subsample_count; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    return info;
}