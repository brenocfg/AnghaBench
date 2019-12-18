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
typedef  int*** sb_int8_array ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*) ; 
 int** coding_method_table ; 
 int /*<<< orphan*/  fix_coding_method_array (int,int,int***) ; 
 int** tone_level_idx_offset_table ; 

__attribute__((used)) static void fill_coding_method_array(sb_int8_array tone_level_idx,
                                     sb_int8_array tone_level_idx_temp,
                                     sb_int8_array coding_method,
                                     int nb_channels,
                                     int c, int superblocktype_2_3,
                                     int cm_table_select)
{
    int ch, sb, j;
    int tmp, acc, esp_40, comp;
    int add1, add2, add3, add4;
    int64_t multres;

    if (!superblocktype_2_3) {
        /* This case is untested, no samples available */
        avpriv_request_sample(NULL, "!superblocktype_2_3");
        return;
        for (ch = 0; ch < nb_channels; ch++) {
            for (sb = 0; sb < 30; sb++) {
                for (j = 1; j < 63; j++) {  // The loop only iterates to 63 so the code doesn't overflow the buffer
                    add1 = tone_level_idx[ch][sb][j] - 10;
                    if (add1 < 0)
                        add1 = 0;
                    add2 = add3 = add4 = 0;
                    if (sb > 1) {
                        add2 = tone_level_idx[ch][sb - 2][j] + tone_level_idx_offset_table[sb][0] - 6;
                        if (add2 < 0)
                            add2 = 0;
                    }
                    if (sb > 0) {
                        add3 = tone_level_idx[ch][sb - 1][j] + tone_level_idx_offset_table[sb][1] - 6;
                        if (add3 < 0)
                            add3 = 0;
                    }
                    if (sb < 29) {
                        add4 = tone_level_idx[ch][sb + 1][j] + tone_level_idx_offset_table[sb][3] - 6;
                        if (add4 < 0)
                            add4 = 0;
                    }
                    tmp = tone_level_idx[ch][sb][j + 1] * 2 - add4 - add3 - add2 - add1;
                    if (tmp < 0)
                        tmp = 0;
                    tone_level_idx_temp[ch][sb][j + 1] = tmp & 0xff;
                }
                tone_level_idx_temp[ch][sb][0] = tone_level_idx_temp[ch][sb][1];
            }
        }
        acc = 0;
        for (ch = 0; ch < nb_channels; ch++)
            for (sb = 0; sb < 30; sb++)
                for (j = 0; j < 64; j++)
                    acc += tone_level_idx_temp[ch][sb][j];

        multres = 0x66666667LL * (acc * 10);
        esp_40 = (multres >> 32) / 8 + ((multres & 0xffffffff) >> 31);
        for (ch = 0;  ch < nb_channels; ch++)
            for (sb = 0; sb < 30; sb++)
                for (j = 0; j < 64; j++) {
                    comp = tone_level_idx_temp[ch][sb][j]* esp_40 * 10;
                    if (comp < 0)
                        comp += 0xff;
                    comp /= 256; // signed shift
                    switch(sb) {
                        case 0:
                            if (comp < 30)
                                comp = 30;
                            comp += 15;
                            break;
                        case 1:
                            if (comp < 24)
                                comp = 24;
                            comp += 10;
                            break;
                        case 2:
                        case 3:
                        case 4:
                            if (comp < 16)
                                comp = 16;
                    }
                    if (comp <= 5)
                        tmp = 0;
                    else if (comp <= 10)
                        tmp = 10;
                    else if (comp <= 16)
                        tmp = 16;
                    else if (comp <= 24)
                        tmp = -1;
                    else
                        tmp = 0;
                    coding_method[ch][sb][j] = ((tmp & 0xfffa) + 30 )& 0xff;
                }
        for (sb = 0; sb < 30; sb++)
            fix_coding_method_array(sb, nb_channels, coding_method);
        for (ch = 0; ch < nb_channels; ch++)
            for (sb = 0; sb < 30; sb++)
                for (j = 0; j < 64; j++)
                    if (sb >= 10) {
                        if (coding_method[ch][sb][j] < 10)
                            coding_method[ch][sb][j] = 10;
                    } else {
                        if (sb >= 2) {
                            if (coding_method[ch][sb][j] < 16)
                                coding_method[ch][sb][j] = 16;
                        } else {
                            if (coding_method[ch][sb][j] < 30)
                                coding_method[ch][sb][j] = 30;
                        }
                    }
    } else { // superblocktype_2_3 != 0
        for (ch = 0; ch < nb_channels; ch++)
            for (sb = 0; sb < 30; sb++)
                for (j = 0; j < 64; j++)
                    coding_method[ch][sb][j] = coding_method_table[cm_table_select][sb];
    }
}