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
typedef  int int32_t ;
typedef  int int16_t ;
typedef  int* DCTBLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN32A (int /*<<< orphan*/ *,int) ; 
 int CONST_BITS ; 
 int DCTSIZE ; 
 size_t DCTSTRIDE ; 
 scalar_t__ DESCALE (int,int) ; 
 int /*<<< orphan*/  FIX_0_541196100 ; 
 int /*<<< orphan*/  FIX_0_765366865 ; 
 int /*<<< orphan*/  FIX_1_306562965 ; 
 int /*<<< orphan*/  FIX_1_847759065 ; 
 int MULTIPLY (int,int /*<<< orphan*/ ) ; 
 int PASS1_BITS ; 

void ff_j_rev_dct4(DCTBLOCK data)
{
  int32_t tmp0, tmp1, tmp2, tmp3;
  int32_t tmp10, tmp11, tmp12, tmp13;
  int32_t z1;
  int32_t d0, d2, d4, d6;
  register int16_t *dataptr;
  int rowctr;

  /* Pass 1: process rows. */
  /* Note results are scaled up by sqrt(8) compared to a true IDCT; */
  /* furthermore, we scale the results by 2**PASS1_BITS. */

  data[0] += 4;

  dataptr = data;

  for (rowctr = DCTSIZE-1; rowctr >= 0; rowctr--) {
    /* Due to quantization, we will usually find that many of the input
     * coefficients are zero, especially the AC terms.  We can exploit this
     * by short-circuiting the IDCT calculation for any row in which all
     * the AC terms are zero.  In that case each output is equal to the
     * DC coefficient (with scale factor as needed).
     * With typical images and quantization tables, half or more of the
     * row DCT calculations can be simplified this way.
     */

    register uint8_t *idataptr = (uint8_t*)dataptr;

    d0 = dataptr[0];
    d2 = dataptr[1];
    d4 = dataptr[2];
    d6 = dataptr[3];

    if ((d2 | d4 | d6) == 0) {
      /* AC terms all zero */
      if (d0) {
          /* Compute a 32 bit value to assign. */
          int16_t dcval = (int16_t) (d0 << PASS1_BITS);
          register int v = (dcval & 0xffff) | ((dcval << 16) & 0xffff0000);

          AV_WN32A(&idataptr[0], v);
          AV_WN32A(&idataptr[4], v);
      }

      dataptr += DCTSTRIDE;     /* advance pointer to next row */
      continue;
    }

    /* Even part: reverse the even part of the forward DCT. */
    /* The rotator is sqrt(2)*c(-6). */
    if (d6) {
            if (d2) {
                    /* d0 != 0, d2 != 0, d4 != 0, d6 != 0 */
                    z1 = MULTIPLY(d2 + d6, FIX_0_541196100);
                    tmp2 = z1 + MULTIPLY(-d6, FIX_1_847759065);
                    tmp3 = z1 + MULTIPLY(d2, FIX_0_765366865);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            } else {
                    /* d0 != 0, d2 == 0, d4 != 0, d6 != 0 */
                    tmp2 = MULTIPLY(-d6, FIX_1_306562965);
                    tmp3 = MULTIPLY(d6, FIX_0_541196100);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            }
    } else {
            if (d2) {
                    /* d0 != 0, d2 != 0, d4 != 0, d6 == 0 */
                    tmp2 = MULTIPLY(d2, FIX_0_541196100);
                    tmp3 = MULTIPLY(d2, FIX_1_306562965);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            } else {
                    /* d0 != 0, d2 == 0, d4 != 0, d6 == 0 */
                    tmp10 = tmp13 = (d0 + d4) << CONST_BITS;
                    tmp11 = tmp12 = (d0 - d4) << CONST_BITS;
            }
      }

    /* Final output stage: inputs are tmp10..tmp13, tmp0..tmp3 */

    dataptr[0] = (int16_t) DESCALE(tmp10, CONST_BITS-PASS1_BITS);
    dataptr[1] = (int16_t) DESCALE(tmp11, CONST_BITS-PASS1_BITS);
    dataptr[2] = (int16_t) DESCALE(tmp12, CONST_BITS-PASS1_BITS);
    dataptr[3] = (int16_t) DESCALE(tmp13, CONST_BITS-PASS1_BITS);

    dataptr += DCTSTRIDE;       /* advance pointer to next row */
  }

  /* Pass 2: process columns. */
  /* Note that we must descale the results by a factor of 8 == 2**3, */
  /* and also undo the PASS1_BITS scaling. */

  dataptr = data;
  for (rowctr = DCTSIZE-1; rowctr >= 0; rowctr--) {
    /* Columns of zeroes can be exploited in the same way as we did with rows.
     * However, the row calculation has created many nonzero AC terms, so the
     * simplification applies less often (typically 5% to 10% of the time).
     * On machines with very fast multiplication, it's possible that the
     * test takes more time than it's worth.  In that case this section
     * may be commented out.
     */

    d0 = dataptr[DCTSTRIDE*0];
    d2 = dataptr[DCTSTRIDE*1];
    d4 = dataptr[DCTSTRIDE*2];
    d6 = dataptr[DCTSTRIDE*3];

    /* Even part: reverse the even part of the forward DCT. */
    /* The rotator is sqrt(2)*c(-6). */
    if (d6) {
            if (d2) {
                    /* d0 != 0, d2 != 0, d4 != 0, d6 != 0 */
                    z1 = MULTIPLY(d2 + d6, FIX_0_541196100);
                    tmp2 = z1 + MULTIPLY(-d6, FIX_1_847759065);
                    tmp3 = z1 + MULTIPLY(d2, FIX_0_765366865);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            } else {
                    /* d0 != 0, d2 == 0, d4 != 0, d6 != 0 */
                    tmp2 = MULTIPLY(-d6, FIX_1_306562965);
                    tmp3 = MULTIPLY(d6, FIX_0_541196100);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            }
    } else {
            if (d2) {
                    /* d0 != 0, d2 != 0, d4 != 0, d6 == 0 */
                    tmp2 = MULTIPLY(d2, FIX_0_541196100);
                    tmp3 = MULTIPLY(d2, FIX_1_306562965);

                    tmp0 = (d0 + d4) << CONST_BITS;
                    tmp1 = (d0 - d4) << CONST_BITS;

                    tmp10 = tmp0 + tmp3;
                    tmp13 = tmp0 - tmp3;
                    tmp11 = tmp1 + tmp2;
                    tmp12 = tmp1 - tmp2;
            } else {
                    /* d0 != 0, d2 == 0, d4 != 0, d6 == 0 */
                    tmp10 = tmp13 = (d0 + d4) << CONST_BITS;
                    tmp11 = tmp12 = (d0 - d4) << CONST_BITS;
            }
    }

    /* Final output stage: inputs are tmp10..tmp13, tmp0..tmp3 */

    dataptr[DCTSTRIDE*0] = tmp10 >> (CONST_BITS+PASS1_BITS+3);
    dataptr[DCTSTRIDE*1] = tmp11 >> (CONST_BITS+PASS1_BITS+3);
    dataptr[DCTSTRIDE*2] = tmp12 >> (CONST_BITS+PASS1_BITS+3);
    dataptr[DCTSTRIDE*3] = tmp13 >> (CONST_BITS+PASS1_BITS+3);

    dataptr++;                  /* advance pointer to next column */
  }
}