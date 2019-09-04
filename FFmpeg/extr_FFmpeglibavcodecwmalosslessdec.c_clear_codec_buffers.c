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
struct TYPE_5__ {int num_channels; int* cdlms_ttl; scalar_t__* ave_sum; TYPE_1__** cdlms; int /*<<< orphan*/  mclms_updates; int /*<<< orphan*/  mclms_prevvalues; int /*<<< orphan*/  mclms_coeffs_cur; int /*<<< orphan*/  mclms_coeffs; int /*<<< orphan*/  lpc_coefs; int /*<<< orphan*/  acfilter_prevvalues; int /*<<< orphan*/  acfilter_coeffs; } ;
typedef  TYPE_2__ WmallDecodeCtx ;
struct TYPE_4__ {int /*<<< orphan*/  lms_updates; int /*<<< orphan*/  lms_prevvalues; int /*<<< orphan*/  coefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_codec_buffers(WmallDecodeCtx *s)
{
    int ich, ilms;

    memset(s->acfilter_coeffs,     0, sizeof(s->acfilter_coeffs));
    memset(s->acfilter_prevvalues, 0, sizeof(s->acfilter_prevvalues));
    memset(s->lpc_coefs,           0, sizeof(s->lpc_coefs));

    memset(s->mclms_coeffs,     0, sizeof(s->mclms_coeffs));
    memset(s->mclms_coeffs_cur, 0, sizeof(s->mclms_coeffs_cur));
    memset(s->mclms_prevvalues, 0, sizeof(s->mclms_prevvalues));
    memset(s->mclms_updates,    0, sizeof(s->mclms_updates));

    for (ich = 0; ich < s->num_channels; ich++) {
        for (ilms = 0; ilms < s->cdlms_ttl[ich]; ilms++) {
            memset(s->cdlms[ich][ilms].coefs, 0,
                   sizeof(s->cdlms[ich][ilms].coefs));
            memset(s->cdlms[ich][ilms].lms_prevvalues, 0,
                   sizeof(s->cdlms[ich][ilms].lms_prevvalues));
            memset(s->cdlms[ich][ilms].lms_updates, 0,
                   sizeof(s->cdlms[ich][ilms].lms_updates));
        }
        s->ave_sum[ich] = 0;
    }
}