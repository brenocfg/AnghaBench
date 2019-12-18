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
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_AUTOMATIC ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR_CODE (int) ; 
 int /*<<< orphan*/  HEX_DIGIT_TEST (int) ; 
 unsigned int HEX_DIGIT_VAL (int) ; 
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_utf8 (int /*<<< orphan*/ *,unsigned int) ; 
 int expect_byte (int /*<<< orphan*/ *,int*,char) ; 
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int parse_string(AVIOContext *pb, int *cur_byte, AVBPrint *bp, int full)
{
    int ret;

    av_bprint_init(bp, 0, full ? AV_BPRINT_SIZE_UNLIMITED : AV_BPRINT_SIZE_AUTOMATIC);
    ret = expect_byte(pb, cur_byte, '"');
    if (ret < 0)
        goto fail;
    while (*cur_byte > 0 && *cur_byte != '"') {
        if (*cur_byte == '\\') {
            next_byte(pb, cur_byte);
            if (*cur_byte < 0) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            if ((*cur_byte | 32) == 'u') {
                unsigned chr = 0, i;
                for (i = 0; i < 4; i++) {
                    next_byte(pb, cur_byte);
                    if (!HEX_DIGIT_TEST(*cur_byte)) {
                        ret = ERR_CODE(*cur_byte);
                        goto fail;
                    }
                    chr = chr * 16 + HEX_DIGIT_VAL(*cur_byte);
                }
                av_bprint_utf8(bp, chr);
            } else {
                av_bprint_chars(bp, *cur_byte, 1);
            }
        } else {
            av_bprint_chars(bp, *cur_byte, 1);
        }
        next_byte(pb, cur_byte);
    }
    ret = expect_byte(pb, cur_byte, '"');
    if (ret < 0)
        goto fail;
    if (full && !av_bprint_is_complete(bp)) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    return 0;

fail:
    av_bprint_finalize(bp, NULL);
    return ret;
}