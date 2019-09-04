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
struct AVBPrint {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {char* extradata; int /*<<< orphan*/  extradata_size; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_bprint_finalize (struct AVBPrint*,char**) ; 
 int /*<<< orphan*/  av_bprint_is_complete (struct AVBPrint*) ; 
 int /*<<< orphan*/  av_free (char*) ; 

int ff_bprint_to_codecpar_extradata(AVCodecParameters *par, struct AVBPrint *buf)
{
    int ret;
    char *str;

    ret = av_bprint_finalize(buf, &str);
    if (ret < 0)
        return ret;
    if (!av_bprint_is_complete(buf)) {
        av_free(str);
        return AVERROR(ENOMEM);
    }

    par->extradata = str;
    /* Note: the string is NUL terminated (so extradata can be read as a
     * string), but the ending character is not accounted in the size (in
     * binary formats you are likely not supposed to mux that character). When
     * extradata is copied, it is also padded with AV_INPUT_BUFFER_PADDING_SIZE
     * zeros. */
    par->extradata_size = buf->len;
    return 0;
}