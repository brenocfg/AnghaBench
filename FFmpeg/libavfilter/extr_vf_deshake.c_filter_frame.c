#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_36__ {float x; float y; } ;
struct TYPE_31__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_37__ {float angle; float zoom; TYPE_6__ vec; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_7__ Transform ;
struct TYPE_39__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_34__ {double x; double y; } ;
struct TYPE_35__ {double angle; double zoom; TYPE_4__ vec; } ;
struct TYPE_32__ {float x; float y; } ;
struct TYPE_33__ {float angle; float zoom; TYPE_2__ vec; } ;
struct TYPE_38__ {double refcount; scalar_t__ cx; scalar_t__ cy; int cw; scalar_t__ ch; int (* transform ) (TYPE_12__*,int const,int const,int const,int const,float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,TYPE_10__*) ;TYPE_10__* ref; int /*<<< orphan*/  edge; TYPE_5__ last; scalar_t__ fp; TYPE_3__ avg; int /*<<< orphan*/  sad; } ;
struct TYPE_30__ {TYPE_11__** outputs; TYPE_8__* priv; } ;
struct TYPE_29__ {unsigned int w; unsigned int h; TYPE_12__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_28__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_8__ DeshakeContext ;
typedef  TYPE_9__ AVPixFmtDescriptor ;
typedef  TYPE_10__ AVFrame ;
typedef  TYPE_11__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFMIN (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  INTERPOLATE_BILINEAR ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_10__**) ; 
 TYPE_9__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pixelutils_get_sad_fn (int,int,int,TYPE_8__*) ; 
 int ff_filter_frame (TYPE_11__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ff_get_matrix (int const,int const,double,float,float,float*) ; 
 TYPE_10__* ff_get_video_buffer (TYPE_11__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  find_motion (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int,TYPE_7__*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,float,int,int,float,int,int,float,int,float,float,float) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int stub1 (TYPE_12__*,int const,int const,int const,int const,float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,TYPE_10__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    DeshakeContext *deshake = link->dst->priv;
    AVFilterLink *outlink = link->dst->outputs[0];
    AVFrame *out;
    Transform t = {{0},0}, orig = {{0},0};
    float matrix_y[9], matrix_uv[9];
    float alpha = 2.0 / deshake->refcount;
    char tmp[256];
    int ret = 0;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(link->format);
    const int chroma_width  = AV_CEIL_RSHIFT(link->w, desc->log2_chroma_w);
    const int chroma_height = AV_CEIL_RSHIFT(link->h, desc->log2_chroma_h);
    int aligned;
    float transform_zoom;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    aligned = !((intptr_t)in->data[0] & 15 | in->linesize[0] & 15);
    deshake->sad = av_pixelutils_get_sad_fn(4, 4, aligned, deshake); // 16x16, 2nd source unaligned
    if (!deshake->sad)
        return AVERROR(EINVAL);

    if (deshake->cx < 0 || deshake->cy < 0 || deshake->cw < 0 || deshake->ch < 0) {
        // Find the most likely global motion for the current frame
        find_motion(deshake, (deshake->ref == NULL) ? in->data[0] : deshake->ref->data[0], in->data[0], link->w, link->h, in->linesize[0], &t);
    } else {
        uint8_t *src1 = (deshake->ref == NULL) ? in->data[0] : deshake->ref->data[0];
        uint8_t *src2 = in->data[0];

        deshake->cx = FFMIN(deshake->cx, link->w);
        deshake->cy = FFMIN(deshake->cy, link->h);

        if ((unsigned)deshake->cx + (unsigned)deshake->cw > link->w) deshake->cw = link->w - deshake->cx;
        if ((unsigned)deshake->cy + (unsigned)deshake->ch > link->h) deshake->ch = link->h - deshake->cy;

        // Quadword align right margin
        deshake->cw &= ~15;

        src1 += deshake->cy * in->linesize[0] + deshake->cx;
        src2 += deshake->cy * in->linesize[0] + deshake->cx;

        find_motion(deshake, src1, src2, deshake->cw, deshake->ch, in->linesize[0], &t);
    }


    // Copy transform so we can output it later to compare to the smoothed value
    orig.vec.x = t.vec.x;
    orig.vec.y = t.vec.y;
    orig.angle = t.angle;
    orig.zoom = t.zoom;

    // Generate a one-sided moving exponential average
    deshake->avg.vec.x = alpha * t.vec.x + (1.0 - alpha) * deshake->avg.vec.x;
    deshake->avg.vec.y = alpha * t.vec.y + (1.0 - alpha) * deshake->avg.vec.y;
    deshake->avg.angle = alpha * t.angle + (1.0 - alpha) * deshake->avg.angle;
    deshake->avg.zoom = alpha * t.zoom + (1.0 - alpha) * deshake->avg.zoom;

    // Remove the average from the current motion to detect the motion that
    // is not on purpose, just as jitter from bumping the camera
    t.vec.x -= deshake->avg.vec.x;
    t.vec.y -= deshake->avg.vec.y;
    t.angle -= deshake->avg.angle;
    t.zoom -= deshake->avg.zoom;

    // Invert the motion to undo it
    t.vec.x *= -1;
    t.vec.y *= -1;
    t.angle *= -1;

    // Write statistics to file
    if (deshake->fp) {
        snprintf(tmp, 256, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", orig.vec.x, deshake->avg.vec.x, t.vec.x, orig.vec.y, deshake->avg.vec.y, t.vec.y, orig.angle, deshake->avg.angle, t.angle, orig.zoom, deshake->avg.zoom, t.zoom);
        fwrite(tmp, sizeof(char), strlen(tmp), deshake->fp);
    }

    // Turn relative current frame motion into absolute by adding it to the
    // last absolute motion
    t.vec.x += deshake->last.vec.x;
    t.vec.y += deshake->last.vec.y;
    t.angle += deshake->last.angle;
    t.zoom += deshake->last.zoom;

    // Shrink motion by 10% to keep things centered in the camera frame
    t.vec.x *= 0.9;
    t.vec.y *= 0.9;
    t.angle *= 0.9;

    // Store the last absolute motion information
    deshake->last.vec.x = t.vec.x;
    deshake->last.vec.y = t.vec.y;
    deshake->last.angle = t.angle;
    deshake->last.zoom = t.zoom;

    transform_zoom = 1.0 + t.zoom / 100.0;

    // Generate a luma transformation matrix
    ff_get_matrix(t.vec.x, t.vec.y, t.angle, transform_zoom, transform_zoom, matrix_y);
    // Generate a chroma transformation matrix
    ff_get_matrix(t.vec.x / (link->w / chroma_width), t.vec.y / (link->h / chroma_height), t.angle, transform_zoom, transform_zoom, matrix_uv);
    // Transform the luma and chroma planes
    ret = deshake->transform(link->dst, link->w, link->h, chroma_width, chroma_height,
                             matrix_y, matrix_uv, INTERPOLATE_BILINEAR, deshake->edge, in, out);

    // Cleanup the old reference frame
    av_frame_free(&deshake->ref);

    if (ret < 0)
        goto fail;

    // Store the current frame as the reference frame for calculating the
    // motion of the next frame
    deshake->ref = in;

    return ff_filter_frame(outlink, out);
fail:
    av_frame_free(&out);
    return ret;
}