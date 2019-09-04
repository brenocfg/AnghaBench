#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int data_size; int type; TYPE_1__* content; int /*<<< orphan*/  data; int /*<<< orphan*/  data_ref; } ;
struct TYPE_10__ {int data_size; scalar_t__ data; int /*<<< orphan*/  data_ref; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ JPEGRawScan ;
typedef  int /*<<< orphan*/  JPEGRawQuantisationTableSpecification ;
typedef  int /*<<< orphan*/  JPEGRawHuffmanTableSpecification ;
typedef  int /*<<< orphan*/  JPEGRawFrameHeader ;
typedef  int /*<<< orphan*/  JPEGRawComment ;
typedef  int /*<<< orphan*/  JPEGRawApplicationData ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int JPEG_MARKER_APPN ; 
#define  JPEG_MARKER_COM 130 
#define  JPEG_MARKER_DHT 129 
#define  JPEG_MARKER_DQT 128 
 int JPEG_MARKER_SOF0 ; 
 int JPEG_MARKER_SOF3 ; 
 int JPEG_MARKER_SOS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbs_jpeg_free_application_data ; 
 int /*<<< orphan*/  cbs_jpeg_free_comment ; 
 int /*<<< orphan*/  cbs_jpeg_free_scan ; 
 int cbs_jpeg_read_application_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_jpeg_read_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_jpeg_read_dht (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_jpeg_read_dqt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_jpeg_read_frame_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cbs_jpeg_read_scan_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_cbs_alloc_unit_content (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cbs_jpeg_read_unit(CodedBitstreamContext *ctx,
                              CodedBitstreamUnit *unit)
{
    GetBitContext gbc;
    int err;

    err = init_get_bits(&gbc, unit->data, 8 * unit->data_size);
    if (err < 0)
        return err;

    if (unit->type >= JPEG_MARKER_SOF0 &&
        unit->type <= JPEG_MARKER_SOF3) {
        err = ff_cbs_alloc_unit_content(ctx, unit,
                                        sizeof(JPEGRawFrameHeader),
                                        NULL);
        if (err < 0)
            return err;

        err = cbs_jpeg_read_frame_header(ctx, &gbc, unit->content);
        if (err < 0)
            return err;

    } else if (unit->type >= JPEG_MARKER_APPN &&
               unit->type <= JPEG_MARKER_APPN + 15) {
        err = ff_cbs_alloc_unit_content(ctx, unit,
                                        sizeof(JPEGRawApplicationData),
                                        &cbs_jpeg_free_application_data);
        if (err < 0)
            return err;

        err = cbs_jpeg_read_application_data(ctx, &gbc, unit->content);
        if (err < 0)
            return err;

    } else if (unit->type == JPEG_MARKER_SOS) {
        JPEGRawScan *scan;
        int pos;

        err = ff_cbs_alloc_unit_content(ctx, unit,
                                        sizeof(JPEGRawScan),
                                        &cbs_jpeg_free_scan);
        if (err < 0)
            return err;
        scan = unit->content;

        err = cbs_jpeg_read_scan_header(ctx, &gbc, &scan->header);
        if (err < 0)
            return err;

        pos = get_bits_count(&gbc);
        av_assert0(pos % 8 == 0);
        if (pos > 0) {
            scan->data_size = unit->data_size - pos / 8;
            scan->data_ref  = av_buffer_ref(unit->data_ref);
            if (!scan->data_ref)
                return AVERROR(ENOMEM);
            scan->data = unit->data + pos / 8;
        }

    } else {
        switch (unit->type) {
#define SEGMENT(marker, type, func, free) \
        case JPEG_MARKER_ ## marker: \
            { \
                err = ff_cbs_alloc_unit_content(ctx, unit, \
                                                sizeof(type), free); \
                if (err < 0) \
                    return err; \
                err = cbs_jpeg_read_ ## func(ctx, &gbc, unit->content); \
                if (err < 0) \
                    return err; \
            } \
            break
            SEGMENT(DQT, JPEGRawQuantisationTableSpecification, dqt, NULL);
            SEGMENT(DHT, JPEGRawHuffmanTableSpecification,      dht, NULL);
            SEGMENT(COM, JPEGRawComment,  comment, &cbs_jpeg_free_comment);
#undef SEGMENT
        default:
            return AVERROR(ENOSYS);
        }
    }

    return 0;
}