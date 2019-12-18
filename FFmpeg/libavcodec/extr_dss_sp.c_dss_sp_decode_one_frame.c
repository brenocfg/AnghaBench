#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {size_t* sf_adaptive_gain; int /*<<< orphan*/ * sf; int /*<<< orphan*/ * pitch_lag; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** working_buffer; int /*<<< orphan*/ * lpc_filter; int /*<<< orphan*/ * vector_buf; int /*<<< orphan*/  err_buf2; int /*<<< orphan*/  filter; int /*<<< orphan*/ * history; TYPE_1__ fparam; } ;
typedef  TYPE_2__ DssSpContext ;

/* Variables and functions */
 int SUBFRAMES ; 
 int /*<<< orphan*/  dss_sp_32to16bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dss_sp_adaptive_gain ; 
 int /*<<< orphan*/  dss_sp_add_pulses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_sp_convert_coeffs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_sp_gen_exc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_sp_sf_synthesis (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dss_sp_shift_sq_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_sp_unpack_coeffs (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dss_sp_unpack_filter (TYPE_2__*) ; 
 int /*<<< orphan*/  dss_sp_update_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_sp_update_state (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dss_sp_decode_one_frame(DssSpContext *p,
                                   int16_t *abuf_dst, const uint8_t *abuf_src)
{
    int i, j;

    dss_sp_unpack_coeffs(p, abuf_src);

    dss_sp_unpack_filter(p);

    dss_sp_convert_coeffs(p->lpc_filter, p->filter);

    for (j = 0; j < SUBFRAMES; j++) {
        dss_sp_gen_exc(p->vector_buf, p->history,
                       p->fparam.pitch_lag[j],
                       dss_sp_adaptive_gain[p->fparam.sf_adaptive_gain[j]]);

        dss_sp_add_pulses(p->vector_buf, &p->fparam.sf[j]);

        dss_sp_update_buf(p->vector_buf, p->history);

        for (i = 0; i < 72; i++)
            p->vector_buf[i] = p->history[72 - i];

        dss_sp_shift_sq_sub(p->filter,
                            p->err_buf2, p->vector_buf);

        dss_sp_sf_synthesis(p, p->lpc_filter[0],
                            &p->working_buffer[j][0], 72);
    }

    dss_sp_update_state(p, &p->working_buffer[0][0]);

    dss_sp_32to16bit(abuf_dst,
                     &p->working_buffer[0][0], 264);
    return 0;
}