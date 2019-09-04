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
struct TYPE_3__ {int type; int /*<<< orphan*/  content; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int JPEG_MARKER_APPN ; 
#define  JPEG_MARKER_COM 130 
#define  JPEG_MARKER_DHT 129 
#define  JPEG_MARKER_DQT 128 
 int JPEG_MARKER_SOF0 ; 
 int JPEG_MARKER_SOF3 ; 
 int cbs_jpeg_write_application_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cbs_jpeg_write_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cbs_jpeg_write_dht (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cbs_jpeg_write_dqt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cbs_jpeg_write_frame_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbs_jpeg_write_segment(CodedBitstreamContext *ctx,
                                  CodedBitstreamUnit *unit,
                                  PutBitContext *pbc)
{
    int err;

    if (unit->type >= JPEG_MARKER_SOF0 &&
        unit->type <= JPEG_MARKER_SOF3) {
        err = cbs_jpeg_write_frame_header(ctx, pbc, unit->content);
    } else if (unit->type >= JPEG_MARKER_APPN &&
               unit->type <= JPEG_MARKER_APPN + 15) {
        err = cbs_jpeg_write_application_data(ctx, pbc, unit->content);
    } else {
        switch (unit->type) {
#define SEGMENT(marker, func) \
            case JPEG_MARKER_ ## marker: \
                err = cbs_jpeg_write_ ## func(ctx, pbc, unit->content); \
                break;
            SEGMENT(DQT, dqt);
            SEGMENT(DHT, dht);
            SEGMENT(COM, comment);
        default:
            return AVERROR_PATCHWELCOME;
        }
    }

    return err;
}