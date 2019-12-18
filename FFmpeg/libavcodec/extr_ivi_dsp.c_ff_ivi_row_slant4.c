#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IVI_INV_SLANT4 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_ivi_row_slant4(const int32_t *in, int16_t *out, ptrdiff_t pitch, const uint8_t *flags)
{
    int     i;
    int     t0, t1, t2, t3, t4;

#define COMPENSATE(x) (((x) + 1)>>1)
    for (i = 0; i < 4; i++) {
        if (!in[0] && !in[1] && !in[2] && !in[3]) {
            memset(out, 0, 4*sizeof(out[0]));
        } else {
            IVI_INV_SLANT4( in[0],  in[1],  in[2],  in[3],
                           out[0], out[1], out[2], out[3],
                           t0, t1, t2, t3, t4);
        }
        in  += 4;
        out += pitch;
    }
#undef COMPENSATE
}