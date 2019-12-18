#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_2__ {int projection; scalar_t__ roll; scalar_t__ pitch; scalar_t__ yaw; int /*<<< orphan*/  padding; int /*<<< orphan*/  bound_right; int /*<<< orphan*/  bound_left; int /*<<< orphan*/  bound_bottom; int /*<<< orphan*/  bound_top; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_1__ AVSphericalMapping ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_DATA_SPHERICAL ; 
#define  AV_SPHERICAL_CUBEMAP 130 
#define  AV_SPHERICAL_EQUIRECTANGULAR 129 
#define  AV_SPHERICAL_EQUIRECTANGULAR_TILE 128 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTION ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTIONPOSEPITCH ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTIONPOSEROLL ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTIONPOSEYAW ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTIONPRIVATE ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOPROJECTIONTYPE ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_PROJECTION_TYPE_CUBEMAP ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_PROJECTION_TYPE_EQUIRECTANGULAR ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_stream_get_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  end_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ebml_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  put_ebml_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mkv_write_video_projection(AVFormatContext *s, AVIOContext *pb,
                                      AVStream *st)
{
    AVIOContext b;
    AVIOContext *dyn_cp;
    int side_data_size = 0;
    int ret, projection_size;
    uint8_t *projection_ptr;
    uint8_t private[20];

    const AVSphericalMapping *spherical =
        (const AVSphericalMapping *)av_stream_get_side_data(st, AV_PKT_DATA_SPHERICAL,
                                                            &side_data_size);

    if (!side_data_size)
        return 0;

    ret = avio_open_dyn_buf(&dyn_cp);
    if (ret < 0)
        return ret;

    switch (spherical->projection) {
    case AV_SPHERICAL_EQUIRECTANGULAR:
        put_ebml_uint(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONTYPE,
                      MATROSKA_VIDEO_PROJECTION_TYPE_EQUIRECTANGULAR);
        break;
    case AV_SPHERICAL_EQUIRECTANGULAR_TILE:
        ffio_init_context(&b, private, 20, 1, NULL, NULL, NULL, NULL);
        put_ebml_uint(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONTYPE,
                      MATROSKA_VIDEO_PROJECTION_TYPE_EQUIRECTANGULAR);
        avio_wb32(&b, 0); // version + flags
        avio_wb32(&b, spherical->bound_top);
        avio_wb32(&b, spherical->bound_bottom);
        avio_wb32(&b, spherical->bound_left);
        avio_wb32(&b, spherical->bound_right);
        put_ebml_binary(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONPRIVATE,
                        private, avio_tell(&b));
        break;
    case AV_SPHERICAL_CUBEMAP:
        ffio_init_context(&b, private, 12, 1, NULL, NULL, NULL, NULL);
        put_ebml_uint(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONTYPE,
                      MATROSKA_VIDEO_PROJECTION_TYPE_CUBEMAP);
        avio_wb32(&b, 0); // version + flags
        avio_wb32(&b, 0); // layout
        avio_wb32(&b, spherical->padding);
        put_ebml_binary(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONPRIVATE,
                        private, avio_tell(&b));
        break;
    default:
        av_log(s, AV_LOG_WARNING, "Unknown projection type\n");
        goto end;
    }

    if (spherical->yaw)
        put_ebml_float(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONPOSEYAW,
                       (double) spherical->yaw   / (1 << 16));
    if (spherical->pitch)
        put_ebml_float(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONPOSEPITCH,
                       (double) spherical->pitch / (1 << 16));
    if (spherical->roll)
        put_ebml_float(dyn_cp, MATROSKA_ID_VIDEOPROJECTIONPOSEROLL,
                       (double) spherical->roll  / (1 << 16));

end:
    projection_size = avio_close_dyn_buf(dyn_cp, &projection_ptr);
    if (projection_size) {
        ebml_master projection = start_ebml_master(pb,
                                                   MATROSKA_ID_VIDEOPROJECTION,
                                                   projection_size);
        avio_write(pb, projection_ptr, projection_size);
        end_ebml_master(pb, projection);
    }
    av_freep(&projection_ptr);

    return 0;
}