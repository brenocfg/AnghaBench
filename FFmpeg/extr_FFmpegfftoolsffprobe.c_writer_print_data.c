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
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_6__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_bprint_chars (TYPE_1__*,unsigned int,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  writer_print_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writer_print_data(WriterContext *wctx, const char *name,
                              uint8_t *data, int size)
{
    AVBPrint bp;
    int offset = 0, l, i;

    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprintf(&bp, "\n");
    while (size) {
        av_bprintf(&bp, "%08x: ", offset);
        l = FFMIN(size, 16);
        for (i = 0; i < l; i++) {
            av_bprintf(&bp, "%02x", data[i]);
            if (i & 1)
                av_bprintf(&bp, " ");
        }
        av_bprint_chars(&bp, ' ', 41 - 2 * i - i / 2);
        for (i = 0; i < l; i++)
            av_bprint_chars(&bp, data[i] - 32U < 95 ? data[i] : '.', 1);
        av_bprintf(&bp, "\n");
        offset += l;
        data   += l;
        size   -= l;
    }
    writer_print_string(wctx, name, bp.str, 0);
    av_bprint_finalize(&bp, NULL);
}