#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int skipped_bytes; int const* data; int const* raw_data; int size; int raw_size; int* rbsp_buffer; int* skipped_bytes_pos; int skipped_bytes_pos_size; } ;
struct TYPE_5__ {int* rbsp_buffer; size_t rbsp_buffer_size; } ;
typedef  TYPE_1__ H2645RBSP ;
typedef  TYPE_2__ H2645NAL ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_reallocp_array (int**,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_h2645_extract_rbsp(const uint8_t *src, int length,
                          H2645RBSP *rbsp, H2645NAL *nal, int small_padding)
{
    int i, si, di;
    uint8_t *dst;

    nal->skipped_bytes = 0;
#define STARTCODE_TEST                                                  \
        if (i + 2 < length && src[i + 1] == 0 && src[i + 2] <= 3) {     \
            if (src[i + 2] != 3 && src[i + 2] != 0) {                   \
                /* startcode, so we must be past the end */             \
                length = i;                                             \
            }                                                           \
            break;                                                      \
        }
#if HAVE_FAST_UNALIGNED
#define FIND_FIRST_ZERO                                                 \
        if (i > 0 && !src[i])                                           \
            i--;                                                        \
        while (src[i])                                                  \
            i++
#if HAVE_FAST_64BIT
    for (i = 0; i + 1 < length; i += 9) {
        if (!((~AV_RN64(src + i) &
               (AV_RN64(src + i) - 0x0100010001000101ULL)) &
              0x8000800080008080ULL))
            continue;
        FIND_FIRST_ZERO;
        STARTCODE_TEST;
        i -= 7;
    }
#else
    for (i = 0; i + 1 < length; i += 5) {
        if (!((~AV_RN32(src + i) &
               (AV_RN32(src + i) - 0x01000101U)) &
              0x80008080U))
            continue;
        FIND_FIRST_ZERO;
        STARTCODE_TEST;
        i -= 3;
    }
#endif /* HAVE_FAST_64BIT */
#else
    for (i = 0; i + 1 < length; i += 2) {
        if (src[i])
            continue;
        if (i > 0 && src[i - 1] == 0)
            i--;
        STARTCODE_TEST;
    }
#endif /* HAVE_FAST_UNALIGNED */

    if (i >= length - 1 && small_padding) { // no escaped 0
        nal->data     =
        nal->raw_data = src;
        nal->size     =
        nal->raw_size = length;
        return length;
    } else if (i > length)
        i = length;

    nal->rbsp_buffer = &rbsp->rbsp_buffer[rbsp->rbsp_buffer_size];
    dst = nal->rbsp_buffer;

    memcpy(dst, src, i);
    si = di = i;
    while (si + 2 < length) {
        // remove escapes (very rare 1:2^22)
        if (src[si + 2] > 3) {
            dst[di++] = src[si++];
            dst[di++] = src[si++];
        } else if (src[si] == 0 && src[si + 1] == 0 && src[si + 2] != 0) {
            if (src[si + 2] == 3) { // escape
                dst[di++] = 0;
                dst[di++] = 0;
                si       += 3;

                if (nal->skipped_bytes_pos) {
                    nal->skipped_bytes++;
                    if (nal->skipped_bytes_pos_size < nal->skipped_bytes) {
                        nal->skipped_bytes_pos_size *= 2;
                        av_assert0(nal->skipped_bytes_pos_size >= nal->skipped_bytes);
                        av_reallocp_array(&nal->skipped_bytes_pos,
                                nal->skipped_bytes_pos_size,
                                sizeof(*nal->skipped_bytes_pos));
                        if (!nal->skipped_bytes_pos) {
                            nal->skipped_bytes_pos_size = 0;
                            return AVERROR(ENOMEM);
                        }
                    }
                    if (nal->skipped_bytes_pos)
                        nal->skipped_bytes_pos[nal->skipped_bytes-1] = di - 1;
                }
                continue;
            } else // next start code
                goto nsc;
        }

        dst[di++] = src[si++];
    }
    while (si < length)
        dst[di++] = src[si++];

nsc:
    memset(dst + di, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    nal->data = dst;
    nal->size = di;
    nal->raw_data = src;
    nal->raw_size = si;
    rbsp->rbsp_buffer_size += si;

    return si;
}