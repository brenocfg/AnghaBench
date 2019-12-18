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
struct TYPE_5__ {TYPE_1__* content; } ;
struct TYPE_4__ {int data_size; int /*<<< orphan*/ * data; int /*<<< orphan*/  header; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ JPEGRawScan ;
typedef  TYPE_2__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int cbs_jpeg_write_scan_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int put_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_jpeg_write_scan(CodedBitstreamContext *ctx,
                               CodedBitstreamUnit *unit,
                               PutBitContext *pbc)
{
    JPEGRawScan *scan = unit->content;
    int i, err;

    err = cbs_jpeg_write_scan_header(ctx, pbc, &scan->header);
    if (err < 0)
        return err;

    if (scan->data) {
        if (scan->data_size * 8 > put_bits_left(pbc))
            return AVERROR(ENOSPC);

        for (i = 0; i < scan->data_size; i++)
            put_bits(pbc, 8, scan->data[i]);
    }

    return 0;
}