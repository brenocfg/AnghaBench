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
struct TYPE_4__ {struct TYPE_4__* subsamples; struct TYPE_4__* iv; struct TYPE_4__* key_id; } ;
typedef  TYPE_1__ AVEncryptionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 

void av_encryption_info_free(AVEncryptionInfo *info)
{
    if (info) {
        av_free(info->key_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}