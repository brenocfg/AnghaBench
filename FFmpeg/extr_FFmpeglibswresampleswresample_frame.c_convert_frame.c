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
struct TYPE_4__ {int nb_samples; int /*<<< orphan*/ ** extended_data; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int swr_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static inline int convert_frame(SwrContext *s,
                                AVFrame *out, const AVFrame *in)
{
    int ret;
    uint8_t **out_data = NULL;
    const uint8_t **in_data = NULL;
    int out_nb_samples = 0, in_nb_samples = 0;

    if (out) {
        out_data       = out->extended_data;
        out_nb_samples = out->nb_samples;
    }

    if (in) {
        in_data       = (const uint8_t **)in->extended_data;
        in_nb_samples = in->nb_samples;
    }

    ret = swr_convert(s, out_data, out_nb_samples, in_data, in_nb_samples);

    if (ret < 0) {
        if (out)
            out->nb_samples = 0;
        return ret;
    }

    if (out)
        out->nb_samples = ret;

    return 0;
}