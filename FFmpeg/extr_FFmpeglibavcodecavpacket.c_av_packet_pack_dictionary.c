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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 size_t const INT_MAX ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_realloc (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

uint8_t *av_packet_pack_dictionary(AVDictionary *dict, int *size)
{
    AVDictionaryEntry *t = NULL;
    uint8_t *data = NULL;
    *size = 0;

    if (!dict)
        return NULL;

    while ((t = av_dict_get(dict, "", t, AV_DICT_IGNORE_SUFFIX))) {
        const size_t keylen   = strlen(t->key);
        const size_t valuelen = strlen(t->value);
        const size_t new_size = *size + keylen + 1 + valuelen + 1;
        uint8_t *const new_data = av_realloc(data, new_size);

        if (!new_data)
            goto fail;
        data = new_data;
        if (new_size > INT_MAX)
            goto fail;

        memcpy(data + *size, t->key, keylen + 1);
        memcpy(data + *size + keylen + 1, t->value, valuelen + 1);

        *size = new_size;
    }

    return data;

fail:
    av_freep(&data);
    *size = 0;
    return NULL;
}