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
struct TYPE_4__ {int offset; scalar_t__ type; } ;
typedef  TYPE_1__ AVOption ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  const AVClass ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_OPT_TYPE_BINARY ; 
 scalar_t__ AV_OPT_TYPE_CONST ; 
 scalar_t__ AV_OPT_TYPE_DICT ; 
 scalar_t__ AV_OPT_TYPE_STRING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ av_dict_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_memdup (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* av_opt_next (void const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * av_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int opt_size (scalar_t__) ; 

int av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    int ret = 0;

    if (!src)
        return AVERROR(EINVAL);

    c = *(AVClass **)src;
    if (!c || c != *(AVClass **)dst)
        return AVERROR(EINVAL);

    while ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;
        uint8_t **field_dst8 = (uint8_t **)field_dst;
        uint8_t **field_src8 = (uint8_t **)field_src;

        if (o->type == AV_OPT_TYPE_STRING) {
            if (*field_dst8 != *field_src8)
                av_freep(field_dst8);
            *field_dst8 = av_strdup(*field_src8);
            if (*field_src8 && !*field_dst8)
                ret = AVERROR(ENOMEM);
        } else if (o->type == AV_OPT_TYPE_BINARY) {
            int len = *(int *)(field_src8 + 1);
            if (*field_dst8 != *field_src8)
                av_freep(field_dst8);
            *field_dst8 = av_memdup(*field_src8, len);
            if (len && !*field_dst8) {
                ret = AVERROR(ENOMEM);
                len = 0;
            }
            *(int *)(field_dst8 + 1) = len;
        } else if (o->type == AV_OPT_TYPE_CONST) {
            // do nothing
        } else if (o->type == AV_OPT_TYPE_DICT) {
            AVDictionary **sdict = (AVDictionary **) field_src;
            AVDictionary **ddict = (AVDictionary **) field_dst;
            if (*sdict != *ddict)
                av_dict_free(ddict);
            *ddict = NULL;
            av_dict_copy(ddict, *sdict, 0);
            if (av_dict_count(*sdict) != av_dict_count(*ddict))
                ret = AVERROR(ENOMEM);
        } else {
            int size = opt_size(o->type);
            if (size < 0)
                ret = size;
            else
                memcpy(field_dst, field_src, size);
        }
    }
    return ret;
}