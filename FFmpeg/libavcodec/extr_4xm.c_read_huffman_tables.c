#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  up ;
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  pre_vlc; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ FourXContext ;

/* Variables and functions */
 int /*<<< orphan*/  ACDC_VLC_BITS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 scalar_t__ init_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int,int,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static const uint8_t *read_huffman_tables(FourXContext *f,
                                          const uint8_t * const buf,
                                          int buf_size)
{
    int frequency[512] = { 0 };
    uint8_t flag[512];
    int up[512];
    uint8_t len_tab[257];
    int bits_tab[257];
    int start, end;
    const uint8_t *ptr = buf;
    const uint8_t *ptr_end = buf + buf_size;
    int j;

    memset(up, -1, sizeof(up));

    start = *ptr++;
    end   = *ptr++;
    for (;;) {
        int i;

        if (ptr_end - ptr < FFMAX(end - start + 1, 0) + 1) {
            av_log(f->avctx, AV_LOG_ERROR, "invalid data in read_huffman_tables\n");
            return NULL;
        }

        for (i = start; i <= end; i++)
            frequency[i] = *ptr++;
        start = *ptr++;
        if (start == 0)
            break;

        end = *ptr++;
    }
    frequency[256] = 1;

    while ((ptr - buf) & 3)
        ptr++; // 4byte align

    if (ptr > ptr_end) {
        av_log(f->avctx, AV_LOG_ERROR, "ptr overflow in read_huffman_tables\n");
        return NULL;
    }

    for (j = 257; j < 512; j++) {
        int min_freq[2] = { 256 * 256, 256 * 256 };
        int smallest[2] = { 0, 0 };
        int i;
        for (i = 0; i < j; i++) {
            if (frequency[i] == 0)
                continue;
            if (frequency[i] < min_freq[1]) {
                if (frequency[i] < min_freq[0]) {
                    min_freq[1] = min_freq[0];
                    smallest[1] = smallest[0];
                    min_freq[0] = frequency[i];
                    smallest[0] = i;
                } else {
                    min_freq[1] = frequency[i];
                    smallest[1] = i;
                }
            }
        }
        if (min_freq[1] == 256 * 256)
            break;

        frequency[j]           = min_freq[0] + min_freq[1];
        flag[smallest[0]]      = 0;
        flag[smallest[1]]      = 1;
        up[smallest[0]]        =
        up[smallest[1]]        = j;
        frequency[smallest[0]] = frequency[smallest[1]] = 0;
    }

    for (j = 0; j < 257; j++) {
        int node, len = 0, bits = 0;

        for (node = j; up[node] != -1; node = up[node]) {
            bits += flag[node] << len;
            len++;
            if (len > 31)
                // can this happen at all ?
                av_log(f->avctx, AV_LOG_ERROR,
                       "vlc length overflow\n");
        }

        bits_tab[j] = bits;
        len_tab[j]  = len;
    }

    ff_free_vlc(&f->pre_vlc);
    if (init_vlc(&f->pre_vlc, ACDC_VLC_BITS, 257, len_tab, 1, 1,
                 bits_tab, 4, 4, 0))
        return NULL;

    return ptr;
}