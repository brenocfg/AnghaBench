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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int num_coeff_partitions; int* coeff_partition_size; int /*<<< orphan*/ * coeff_partition; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ VP8Context ;

/* Variables and functions */
 int AV_RL24 (int /*<<< orphan*/  const*) ; 
 int ff_vp56_init_range_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int vp8_rac_get_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int setup_partitions(VP8Context *s, const uint8_t *buf, int buf_size)
{
    const uint8_t *sizes = buf;
    int i;
    int ret;

    s->num_coeff_partitions = 1 << vp8_rac_get_uint(&s->c, 2);

    buf      += 3 * (s->num_coeff_partitions - 1);
    buf_size -= 3 * (s->num_coeff_partitions - 1);
    if (buf_size < 0)
        return -1;

    for (i = 0; i < s->num_coeff_partitions - 1; i++) {
        int size = AV_RL24(sizes + 3 * i);
        if (buf_size - size < 0)
            return -1;
        s->coeff_partition_size[i] = size;

        ret = ff_vp56_init_range_decoder(&s->coeff_partition[i], buf, size);
        if (ret < 0)
            return ret;
        buf      += size;
        buf_size -= size;
    }

    s->coeff_partition_size[i] = buf_size;
    ff_vp56_init_range_decoder(&s->coeff_partition[i], buf, buf_size);

    return 0;
}