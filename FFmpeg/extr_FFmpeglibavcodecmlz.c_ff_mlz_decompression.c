#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int freeze_flag; int current_dic_index_max; int next_code; int /*<<< orphan*/  context; scalar_t__ bump_code; int /*<<< orphan*/  dic_code_bit; int /*<<< orphan*/ * dict; } ;
typedef  int /*<<< orphan*/  MLZDict ;
typedef  TYPE_1__ MLZ ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  FLUSH_CODE 130 
#define  FREEZE_CODE 129 
#define  MAX_CODE 128 
 int /*<<< orphan*/  TABLE_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int decode_string (TYPE_1__*,unsigned char*,int,int*,int) ; 
 int /*<<< orphan*/  ff_mlz_flush_dict (TYPE_1__*) ; 
 int input_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_entry_dict (int /*<<< orphan*/ *,int,int,int) ; 

int ff_mlz_decompression(MLZ* mlz, GetBitContext* gb, int size, unsigned char *buff) {
    MLZDict *dict = mlz->dict;
    unsigned long output_chars;
    int string_code, last_string_code, char_code;

    string_code = 0;
    char_code   = -1;
    last_string_code = -1;
    output_chars = 0;

    while (output_chars < size) {
        string_code = input_code(gb, mlz->dic_code_bit);
        switch (string_code) {
            case FLUSH_CODE:
            case MAX_CODE:
                ff_mlz_flush_dict(mlz);
                char_code = -1;
                last_string_code = -1;
                break;
            case FREEZE_CODE:
                mlz->freeze_flag = 1;
                break;
            default:
                if (string_code > mlz->current_dic_index_max) {
                    av_log(mlz->context, AV_LOG_ERROR, "String code %d exceeds maximum value of %d.\n", string_code, mlz->current_dic_index_max);
                    return output_chars;
                }
                if (string_code == (int) mlz->bump_code) {
                    ++mlz->dic_code_bit;
                    mlz->current_dic_index_max *= 2;
                    mlz->bump_code = mlz->current_dic_index_max - 1;
                } else {
                    if (string_code >= mlz->next_code) {
                        int ret = decode_string(mlz, &buff[output_chars], last_string_code, &char_code, size - output_chars);
                        if (ret < 0 || ret > size - output_chars) {
                            av_log(mlz->context, AV_LOG_ERROR, "output chars overflow\n");
                            return output_chars;
                        }
                        output_chars += ret;
                        ret = decode_string(mlz, &buff[output_chars], char_code, &char_code, size - output_chars);
                        if (ret < 0 || ret > size - output_chars) {
                            av_log(mlz->context, AV_LOG_ERROR, "output chars overflow\n");
                            return output_chars;
                        }
                        output_chars += ret;
                        set_new_entry_dict(dict, mlz->next_code, last_string_code, char_code);
                        if (mlz->next_code >= TABLE_SIZE - 1) {
                            av_log(mlz->context, AV_LOG_ERROR, "Too many MLZ codes\n");
                            return output_chars;
                        }
                        mlz->next_code++;
                    } else {
                        int ret = decode_string(mlz, &buff[output_chars], string_code, &char_code, size - output_chars);
                        if (ret < 0 || ret > size - output_chars) {
                            av_log(mlz->context, AV_LOG_ERROR, "output chars overflow\n");
                            return output_chars;
                        }
                        output_chars += ret;
                        if (output_chars <= size && !mlz->freeze_flag) {
                            if (last_string_code != -1) {
                                set_new_entry_dict(dict, mlz->next_code, last_string_code, char_code);
                                if (mlz->next_code >= TABLE_SIZE - 1) {
                                    av_log(mlz->context, AV_LOG_ERROR, "Too many MLZ codes\n");
                                    return output_chars;
                                }
                                mlz->next_code++;
                            }
                        } else {
                            break;
                        }
                    }
                    last_string_code = string_code;
                }
                break;
        }
    }
    return output_chars;
}