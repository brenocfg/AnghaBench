#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {scalar_t__ pict_type; } ;
struct TYPE_5__ {int /*<<< orphan*/ *** curr_use_ic; int /*<<< orphan*/ *** curr_lutuv; int /*<<< orphan*/ *** curr_luty; int /*<<< orphan*/ *** next_lutuv; int /*<<< orphan*/ *** last_lutuv; int /*<<< orphan*/ *** aux_lutuv; TYPE_1__ s; int /*<<< orphan*/ *** next_luty; int /*<<< orphan*/ *** last_luty; int /*<<< orphan*/ *** aux_luty; int /*<<< orphan*/ ** next_use_ic; int /*<<< orphan*/ ** last_use_ic; int /*<<< orphan*/ ** aux_use_ic; } ;
typedef  TYPE_2__ VC1Context ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_BI ; 
 int /*<<< orphan*/  INIT_LUT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void rotate_luts(VC1Context *v)
{
#define ROTATE(DEF, L, N, C, A) do {                          \
        if (v->s.pict_type == AV_PICTURE_TYPE_BI || v->s.pict_type == AV_PICTURE_TYPE_B) { \
            C = A;                                            \
        } else {                                              \
            DEF;                                              \
            memcpy(&tmp, L   , sizeof(tmp));                  \
            memcpy(L   , N   , sizeof(tmp));                  \
            memcpy(N   , &tmp, sizeof(tmp));                  \
            C = N;                                            \
        }                                                     \
    } while(0)

    ROTATE(int tmp,             &v->last_use_ic, &v->next_use_ic, v->curr_use_ic, &v->aux_use_ic);
    ROTATE(uint8_t tmp[2][256], v->last_luty,   v->next_luty,   v->curr_luty,   v->aux_luty);
    ROTATE(uint8_t tmp[2][256], v->last_lutuv,  v->next_lutuv,  v->curr_lutuv,  v->aux_lutuv);

    INIT_LUT(32, 0, v->curr_luty[0], v->curr_lutuv[0], 0);
    INIT_LUT(32, 0, v->curr_luty[1], v->curr_lutuv[1], 0);
    *v->curr_use_ic = 0;
}