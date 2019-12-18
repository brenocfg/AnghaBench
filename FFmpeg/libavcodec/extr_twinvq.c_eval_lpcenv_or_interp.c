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
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_4__ {int /*<<< orphan*/  n_lsp; } ;
typedef  TYPE_1__ TwinVQModeTab ;
struct TYPE_5__ {float** cos_tabs; TYPE_1__* mtab; } ;
typedef  TYPE_2__ TwinVQContext ;

/* Variables and functions */
 float eval_lpc_spectrum (float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cos (int,int,float const*,int) ; 
 int /*<<< orphan*/  interpolate (float*,float,float,int) ; 

__attribute__((used)) static inline void eval_lpcenv_or_interp(TwinVQContext *tctx,
                                         enum TwinVQFrameType ftype,
                                         float *out, const float *in,
                                         int size, int step, int part)
{
    int i;
    const TwinVQModeTab *mtab = tctx->mtab;
    const float *cos_tab      = tctx->cos_tabs[ftype];

    // Fill the 's'
    for (i = 0; i < size; i += step)
        out[i] =
            eval_lpc_spectrum(in,
                              get_cos(i, part, cos_tab, size),
                              mtab->n_lsp);

    // Fill the 'iiiibiiii'
    for (i = step; i <= size - 2 * step; i += step) {
        if (out[i + step] + out[i - step] > 1.95 * out[i] ||
            out[i + step]                 >= out[i - step]) {
            interpolate(out + i - step + 1, out[i], out[i - step], step - 1);
        } else {
            out[i - step / 2] =
                eval_lpc_spectrum(in,
                                  get_cos(i - step / 2, part, cos_tab, size),
                                  mtab->n_lsp);
            interpolate(out + i - step + 1, out[i - step / 2],
                        out[i - step], step / 2 - 1);
            interpolate(out + i - step / 2 + 1, out[i],
                        out[i - step / 2], step / 2 - 1);
        }
    }

    interpolate(out + size - 2 * step + 1, out[size - step],
                out[size - 2 * step], step - 1);
}