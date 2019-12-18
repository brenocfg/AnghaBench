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
struct TYPE_5__ {int /*<<< orphan*/  context; TYPE_1__* dict; } ;
struct TYPE_4__ {int char_code; int parent_code; int /*<<< orphan*/  match_len; } ;
typedef  TYPE_1__ MLZDict ;
typedef  TYPE_2__ MLZ ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  CODE_UNSET 128 
 int /*<<< orphan*/  DIC_INDEX_MAX ; 
 int FIRST_CODE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int decode_string(MLZ* mlz, unsigned char *buff, int string_code, int *first_char_code, unsigned long bufsize) {
    MLZDict* dict = mlz->dict;
    unsigned long count, offset;
    int current_code, parent_code, tmp_code;

    count            = 0;
    current_code     = string_code;
    *first_char_code = CODE_UNSET;

    while (count < bufsize) {
        switch (current_code) {
        case CODE_UNSET:
            return count;
            break;
        default:
            if (current_code < FIRST_CODE) {
                *first_char_code = current_code;
                buff[0] = current_code;
                count++;
                return count;
            } else {
                offset  = dict[current_code].match_len - 1;
                tmp_code = dict[current_code].char_code;
                if (offset >= bufsize) {
                    av_log(mlz->context, AV_LOG_ERROR, "MLZ offset error.\n");
                    return count;
                }
                buff[offset] = tmp_code;
                count++;
            }
            current_code = dict[current_code].parent_code;
            if ((current_code < 0) || (current_code > (DIC_INDEX_MAX - 1))) {
                av_log(mlz->context, AV_LOG_ERROR, "MLZ dic index error.\n");
                return count;
            }
            if (current_code > FIRST_CODE) {
                parent_code = dict[current_code].parent_code;
                offset = (dict[current_code].match_len) - 1;
                if (parent_code < 0 || parent_code > DIC_INDEX_MAX-1) {
                    av_log(mlz->context, AV_LOG_ERROR, "MLZ dic index error.\n");
                    return count;
                }
                if (( offset > (DIC_INDEX_MAX - 1))) {
                    av_log(mlz->context, AV_LOG_ERROR, "MLZ dic offset error.\n");
                    return count;
                }
            }
            break;
        }
    }
    return count;
}