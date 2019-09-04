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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RN16 (int /*<<< orphan*/  const*) ; 
 int SBC_X_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sbc_enc_process_input_8s(int position, const uint8_t *pcm,
                                    int16_t X[2][SBC_X_BUFFER_SIZE],
                                    int nsamples, int nchannels)
{
    int c;

    /* handle X buffer wraparound */
    if (position < nsamples) {
        for (c = 0; c < nchannels; c++)
            memcpy(&X[c][SBC_X_BUFFER_SIZE - 72], &X[c][position],
                            72 * sizeof(int16_t));
        position = SBC_X_BUFFER_SIZE - 72;
    }

    if (position % 16 == 8) {
        position -= 8;
        nsamples -= 8;
        for (c = 0; c < nchannels; c++) {
            int16_t *x = &X[c][position];
            x[0] = AV_RN16(pcm + 14*nchannels + 2*c);
            x[2] = AV_RN16(pcm + 12*nchannels + 2*c);
            x[3] = AV_RN16(pcm +  0*nchannels + 2*c);
            x[4] = AV_RN16(pcm + 10*nchannels + 2*c);
            x[5] = AV_RN16(pcm +  2*nchannels + 2*c);
            x[6] = AV_RN16(pcm +  8*nchannels + 2*c);
            x[7] = AV_RN16(pcm +  4*nchannels + 2*c);
            x[8] = AV_RN16(pcm +  6*nchannels + 2*c);
        }
        pcm += 16 * nchannels;
    }

    /* copy/permutate audio samples */
    for (; nsamples >= 16; nsamples -= 16, pcm += 32 * nchannels) {
        position -= 16;
        for (c = 0; c < nchannels; c++) {
            int16_t *x = &X[c][position];
            x[0]  = AV_RN16(pcm + 30*nchannels + 2*c);
            x[1]  = AV_RN16(pcm + 14*nchannels + 2*c);
            x[2]  = AV_RN16(pcm + 28*nchannels + 2*c);
            x[3]  = AV_RN16(pcm + 16*nchannels + 2*c);
            x[4]  = AV_RN16(pcm + 26*nchannels + 2*c);
            x[5]  = AV_RN16(pcm + 18*nchannels + 2*c);
            x[6]  = AV_RN16(pcm + 24*nchannels + 2*c);
            x[7]  = AV_RN16(pcm + 20*nchannels + 2*c);
            x[8]  = AV_RN16(pcm + 22*nchannels + 2*c);
            x[9]  = AV_RN16(pcm +  6*nchannels + 2*c);
            x[10] = AV_RN16(pcm + 12*nchannels + 2*c);
            x[11] = AV_RN16(pcm +  0*nchannels + 2*c);
            x[12] = AV_RN16(pcm + 10*nchannels + 2*c);
            x[13] = AV_RN16(pcm +  2*nchannels + 2*c);
            x[14] = AV_RN16(pcm +  8*nchannels + 2*c);
            x[15] = AV_RN16(pcm +  4*nchannels + 2*c);
        }
    }

    if (nsamples == 8) {
        position -= 8;
        for (c = 0; c < nchannels; c++) {
            int16_t *x = &X[c][position];
            x[-7] = AV_RN16(pcm + 14*nchannels + 2*c);
            x[1]  = AV_RN16(pcm +  6*nchannels + 2*c);
            x[2]  = AV_RN16(pcm + 12*nchannels + 2*c);
            x[3]  = AV_RN16(pcm +  0*nchannels + 2*c);
            x[4]  = AV_RN16(pcm + 10*nchannels + 2*c);
            x[5]  = AV_RN16(pcm +  2*nchannels + 2*c);
            x[6]  = AV_RN16(pcm +  8*nchannels + 2*c);
            x[7]  = AV_RN16(pcm +  4*nchannels + 2*c);
        }
    }

    return position;
}