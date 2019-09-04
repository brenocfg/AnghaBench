#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  alloc_mb_height; int /*<<< orphan*/  alloc_mb_width; int /*<<< orphan*/ * ref_index; int /*<<< orphan*/ * motion_val; int /*<<< orphan*/  mb_type; int /*<<< orphan*/  qscale_table; int /*<<< orphan*/  mbskip_table; int /*<<< orphan*/  mb_mean; int /*<<< orphan*/  mc_mb_var; int /*<<< orphan*/  mb_var; TYPE_5__** ref_index_buf; TYPE_5__** motion_val_buf; TYPE_5__* mb_type_buf; TYPE_5__* qscale_table_buf; TYPE_5__* mbskip_table_buf; TYPE_5__* mb_mean_buf; TYPE_5__* mc_mb_var_buf; TYPE_5__* mb_var_buf; } ;
typedef  TYPE_1__ Picture ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_buffer_ref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int /*<<< orphan*/  ff_free_picture_tables (TYPE_1__*) ; 

int ff_update_picture_tables(Picture *dst, Picture *src)
{
     int i;

#define UPDATE_TABLE(table)                                                   \
do {                                                                          \
    if (src->table &&                                                         \
        (!dst->table || dst->table->buffer != src->table->buffer)) {          \
        av_buffer_unref(&dst->table);                                         \
        dst->table = av_buffer_ref(src->table);                               \
        if (!dst->table) {                                                    \
            ff_free_picture_tables(dst);                                      \
            return AVERROR(ENOMEM);                                           \
        }                                                                     \
    }                                                                         \
} while (0)

    UPDATE_TABLE(mb_var_buf);
    UPDATE_TABLE(mc_mb_var_buf);
    UPDATE_TABLE(mb_mean_buf);
    UPDATE_TABLE(mbskip_table_buf);
    UPDATE_TABLE(qscale_table_buf);
    UPDATE_TABLE(mb_type_buf);
    for (i = 0; i < 2; i++) {
        UPDATE_TABLE(motion_val_buf[i]);
        UPDATE_TABLE(ref_index_buf[i]);
    }

    dst->mb_var        = src->mb_var;
    dst->mc_mb_var     = src->mc_mb_var;
    dst->mb_mean       = src->mb_mean;
    dst->mbskip_table  = src->mbskip_table;
    dst->qscale_table  = src->qscale_table;
    dst->mb_type       = src->mb_type;
    for (i = 0; i < 2; i++) {
        dst->motion_val[i] = src->motion_val[i];
        dst->ref_index[i]  = src->ref_index[i];
    }

    dst->alloc_mb_width  = src->alloc_mb_width;
    dst->alloc_mb_height = src->alloc_mb_height;

    return 0;
}