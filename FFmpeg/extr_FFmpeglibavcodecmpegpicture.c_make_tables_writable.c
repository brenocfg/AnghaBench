#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* ref_index_buf; scalar_t__* motion_val_buf; scalar_t__ mb_type_buf; scalar_t__ qscale_table_buf; scalar_t__ mbskip_table_buf; scalar_t__ mb_mean_buf; scalar_t__ mc_mb_var_buf; scalar_t__ mb_var_buf; } ;
typedef  TYPE_1__ Picture ;

/* Variables and functions */
 int av_buffer_make_writable (scalar_t__*) ; 

__attribute__((used)) static int make_tables_writable(Picture *pic)
{
    int ret, i;
#define MAKE_WRITABLE(table) \
do {\
    if (pic->table &&\
       (ret = av_buffer_make_writable(&pic->table)) < 0)\
    return ret;\
} while (0)

    MAKE_WRITABLE(mb_var_buf);
    MAKE_WRITABLE(mc_mb_var_buf);
    MAKE_WRITABLE(mb_mean_buf);
    MAKE_WRITABLE(mbskip_table_buf);
    MAKE_WRITABLE(qscale_table_buf);
    MAKE_WRITABLE(mb_type_buf);

    for (i = 0; i < 2; i++) {
        MAKE_WRITABLE(motion_val_buf[i]);
        MAKE_WRITABLE(ref_index_buf[i]);
    }

    return 0;
}