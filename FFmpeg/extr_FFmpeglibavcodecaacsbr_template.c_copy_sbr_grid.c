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
struct TYPE_4__ {size_t bs_num_env; int* e_a; int /*<<< orphan*/  bs_frame_class; int /*<<< orphan*/  bs_num_noise; int /*<<< orphan*/  bs_amp_res; int /*<<< orphan*/ * t_q; int /*<<< orphan*/ * t_env; int /*<<< orphan*/ * bs_freq_res; int /*<<< orphan*/  t_env_num_env_old; } ;
typedef  TYPE_1__ SBRData ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_sbr_grid(SBRData *dst, const SBRData *src) {
    //These variables are saved from the previous frame rather than copied
    dst->bs_freq_res[0]    = dst->bs_freq_res[dst->bs_num_env];
    dst->t_env_num_env_old = dst->t_env[dst->bs_num_env];
    dst->e_a[0]            = -(dst->e_a[1] != dst->bs_num_env);

    //These variables are read from the bitstream and therefore copied
    memcpy(dst->bs_freq_res+1, src->bs_freq_res+1, sizeof(dst->bs_freq_res)-sizeof(*dst->bs_freq_res));
    memcpy(dst->t_env,         src->t_env,         sizeof(dst->t_env));
    memcpy(dst->t_q,           src->t_q,           sizeof(dst->t_q));
    dst->bs_num_env        = src->bs_num_env;
    dst->bs_amp_res        = src->bs_amp_res;
    dst->bs_num_noise      = src->bs_num_noise;
    dst->bs_frame_class    = src->bs_frame_class;
    dst->e_a[1]            = src->e_a[1];
}