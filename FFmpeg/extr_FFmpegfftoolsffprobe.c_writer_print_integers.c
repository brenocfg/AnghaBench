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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_5__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_RN16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_RN32 (int /*<<< orphan*/ *) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_1__*,char const*,...) ; 
 int /*<<< orphan*/  writer_print_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writer_print_integers(WriterContext *wctx, const char *name,
                                  uint8_t *data, int size, const char *format,
                                  int columns, int bytes, int offset_add)
{
    AVBPrint bp;
    int offset = 0, l, i;

    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprintf(&bp, "\n");
    while (size) {
        av_bprintf(&bp, "%08x: ", offset);
        l = FFMIN(size, columns);
        for (i = 0; i < l; i++) {
            if      (bytes == 1) av_bprintf(&bp, format, *data);
            else if (bytes == 2) av_bprintf(&bp, format, AV_RN16(data));
            else if (bytes == 4) av_bprintf(&bp, format, AV_RN32(data));
            data += bytes;
            size --;
        }
        av_bprintf(&bp, "\n");
        offset += offset_add;
    }
    writer_print_string(wctx, name, bp.str, 0);
    av_bprint_finalize(&bp, NULL);
}