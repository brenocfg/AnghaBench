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
typedef  int uint8_t ;

/* Variables and functions */
 int AV_RB16 (int const*) ; 
 int INT_MAX ; 

int avpriv_split_xiph_headers(const uint8_t *extradata, int extradata_size,
                          int first_header_size, const uint8_t *header_start[3],
                          int header_len[3])
{
    int i;

    if (extradata_size >= 6 && AV_RB16(extradata) == first_header_size) {
        int overall_len = 6;
        for (i=0; i<3; i++) {
            header_len[i] = AV_RB16(extradata);
            extradata += 2;
            header_start[i] = extradata;
            extradata += header_len[i];
            if (overall_len > extradata_size - header_len[i])
                return -1;
            overall_len += header_len[i];
        }
    } else if (extradata_size >= 3 && extradata_size < INT_MAX - 0x1ff && extradata[0] == 2) {
        int overall_len = 3;
        extradata++;
        for (i=0; i<2; i++, extradata++) {
            header_len[i] = 0;
            for (; overall_len < extradata_size && *extradata==0xff; extradata++) {
                header_len[i] += 0xff;
                overall_len   += 0xff + 1;
            }
            header_len[i] += *extradata;
            overall_len   += *extradata;
            if (overall_len > extradata_size)
                return -1;
        }
        header_len[2] = extradata_size - overall_len;
        header_start[0] = extradata;
        header_start[1] = header_start[0] + header_len[0];
        header_start[2] = header_start[1] + header_len[1];
    } else {
        return -1;
    }
    return 0;
}