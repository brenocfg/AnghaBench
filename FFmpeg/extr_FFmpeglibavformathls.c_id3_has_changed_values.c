#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct playlist {TYPE_4__* ctx; int /*<<< orphan*/ * id3_initial; } ;
struct TYPE_15__ {char* key; int /*<<< orphan*/  value; } ;
struct TYPE_14__ {TYPE_1__* buf; } ;
struct TYPE_13__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_2__ attached_pic; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ID3v2ExtraMetaAPIC ;
typedef  TYPE_6__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 TYPE_6__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int id3_has_changed_values(struct playlist *pls, AVDictionary *metadata,
                                  ID3v2ExtraMetaAPIC *apic)
{
    AVDictionaryEntry *entry = NULL;
    AVDictionaryEntry *oldentry;
    /* check that no keys have changed values */
    while ((entry = av_dict_get(metadata, "", entry, AV_DICT_IGNORE_SUFFIX))) {
        oldentry = av_dict_get(pls->id3_initial, entry->key, NULL, AV_DICT_MATCH_CASE);
        if (!oldentry || strcmp(oldentry->value, entry->value) != 0)
            return 1;
    }

    /* check if apic appeared */
    if (apic && (pls->ctx->nb_streams != 2 || !pls->ctx->streams[1]->attached_pic.data))
        return 1;

    if (apic) {
        int size = pls->ctx->streams[1]->attached_pic.size;
        if (size != apic->buf->size - AV_INPUT_BUFFER_PADDING_SIZE)
            return 1;

        if (memcmp(apic->buf->data, pls->ctx->streams[1]->attached_pic.data, size) != 0)
            return 1;
    }

    return 0;
}