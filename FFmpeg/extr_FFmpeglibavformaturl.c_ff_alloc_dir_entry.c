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
struct TYPE_4__ {int size; int modification_timestamp; int access_timestamp; int status_change_timestamp; int user_id; int group_id; int filemode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ AVIODirEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_ENTRY_UNKNOWN ; 
 TYPE_1__* av_mallocz (int) ; 

AVIODirEntry *ff_alloc_dir_entry(void)
{
    AVIODirEntry *entry = av_mallocz(sizeof(AVIODirEntry));
    if (entry) {
        entry->type = AVIO_ENTRY_UNKNOWN;
        entry->size = -1;
        entry->modification_timestamp = -1;
        entry->access_timestamp = -1;
        entry->status_change_timestamp = -1;
        entry->user_id = -1;
        entry->group_id = -1;
        entry->filemode = -1;
    }
    return entry;
}