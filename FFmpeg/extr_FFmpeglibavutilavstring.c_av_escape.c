#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVEscapeMode { ____Placeholder_AVEscapeMode } AVEscapeMode ;
struct TYPE_6__ {int len; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_escape (TYPE_1__*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_1__*) ; 

int av_escape(char **dst, const char *src, const char *special_chars,
              enum AVEscapeMode mode, int flags)
{
    AVBPrint dstbuf;

    av_bprint_init(&dstbuf, 1, AV_BPRINT_SIZE_UNLIMITED);
    av_bprint_escape(&dstbuf, src, special_chars, mode, flags);

    if (!av_bprint_is_complete(&dstbuf)) {
        av_bprint_finalize(&dstbuf, NULL);
        return AVERROR(ENOMEM);
    } else {
        av_bprint_finalize(&dstbuf, dst);
        return dstbuf.len;
    }
}