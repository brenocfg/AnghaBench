#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_25__ {int id; } ;
typedef  TYPE_2__ XvImageFormatValues ;
struct TYPE_26__ {int /*<<< orphan*/  base_id; } ;
typedef  TYPE_3__ XvAdaptorInfo ;
struct TYPE_27__ {int /*<<< orphan*/  colormap; } ;
typedef  TYPE_4__ XWindowAttributes ;
struct TYPE_23__ {char* shmaddr; int /*<<< orphan*/  shmid; int /*<<< orphan*/  readOnly; } ;
struct TYPE_28__ {void* window_height; void* window_width; int /*<<< orphan*/  gc; int /*<<< orphan*/  display; scalar_t__ window; TYPE_14__ yuv_shminfo; TYPE_13__* yuv_image; void* image_height; void* image_width; int /*<<< orphan*/  xv_port; scalar_t__ window_id; int /*<<< orphan*/  wm_delete_message; scalar_t__ window_title; int /*<<< orphan*/  window_y; int /*<<< orphan*/  window_x; int /*<<< orphan*/  display_name; int /*<<< orphan*/  image_format; } ;
typedef  TYPE_5__ XVContext ;
struct TYPE_29__ {int flags; int /*<<< orphan*/  pixel; scalar_t__ blue; scalar_t__ green; scalar_t__ red; } ;
typedef  TYPE_6__ XColor ;
struct TYPE_30__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_32__ {scalar_t__ codec_type; scalar_t__ codec_id; void* height; void* width; int /*<<< orphan*/  format; TYPE_7__ sample_aspect_ratio; } ;
struct TYPE_31__ {int nb_streams; int /*<<< orphan*/  url; TYPE_1__** streams; TYPE_5__* priv_data; } ;
struct TYPE_24__ {TYPE_9__* codecpar; } ;
struct TYPE_22__ {char* data; int /*<<< orphan*/  data_size; } ;
typedef  TYPE_7__ AVRational ;
typedef  TYPE_8__ AVFormatContext ;
typedef  TYPE_9__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int DoBlue ; 
 int DoGreen ; 
 int DoRed ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  False ; 
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 scalar_t__ Success ; 
 int /*<<< orphan*/  XAllocColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XCreateSimpleWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XOpenDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XShmAttach (int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  XStoreName (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XvFreeAdaptorInfo (TYPE_3__*) ; 
 TYPE_2__* XvListImageFormats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ XvQueryAdaptors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,TYPE_3__**) ; 
 TYPE_13__* XvShmCreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,void*,TYPE_14__*) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_rescale (void*,scalar_t__,scalar_t__) ; 
 scalar_t__ av_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xv_get_tag_from_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xv_write_trailer (TYPE_8__*) ; 

__attribute__((used)) static int xv_write_header(AVFormatContext *s)
{
    XVContext *xv = s->priv_data;
    unsigned int num_adaptors;
    XvAdaptorInfo *ai;
    XvImageFormatValues *fv;
    XColor fgcolor;
    XWindowAttributes window_attrs;
    int num_formats = 0, j, tag, ret;
    AVCodecParameters *par = s->streams[0]->codecpar;

    if (   s->nb_streams > 1
        || par->codec_type != AVMEDIA_TYPE_VIDEO
        || par->codec_id   != AV_CODEC_ID_RAWVIDEO) {
        av_log(s, AV_LOG_ERROR, "Only supports one rawvideo stream\n");
        return AVERROR(EINVAL);
    }

    if (!(tag = xv_get_tag_from_format(par->format))) {
        av_log(s, AV_LOG_ERROR,
               "Unsupported pixel format '%s', only yuv420p, uyvy422, yuyv422 are currently supported\n",
               av_get_pix_fmt_name(par->format));
        return AVERROR_PATCHWELCOME;
    }
    xv->image_format = par->format;

    xv->display = XOpenDisplay(xv->display_name);
    if (!xv->display) {
        av_log(s, AV_LOG_ERROR, "Could not open the X11 display '%s'\n", xv->display_name);
        return AVERROR(EINVAL);
    }

    xv->image_width  = par->width;
    xv->image_height = par->height;
    if (!xv->window_width && !xv->window_height) {
        AVRational sar = par->sample_aspect_ratio;
        xv->window_width  = par->width;
        xv->window_height = par->height;
        if (sar.num) {
            if (sar.num > sar.den)
                xv->window_width = av_rescale(xv->window_width, sar.num, sar.den);
            if (sar.num < sar.den)
                xv->window_height = av_rescale(xv->window_height, sar.den, sar.num);
        }
    }
    if (!xv->window_id) {
        xv->window = XCreateSimpleWindow(xv->display, DefaultRootWindow(xv->display),
                                         xv->window_x, xv->window_y,
                                         xv->window_width, xv->window_height,
                                         0, 0, 0);
        if (!xv->window_title) {
            if (!(xv->window_title = av_strdup(s->url))) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
        XStoreName(xv->display, xv->window, xv->window_title);
        xv->wm_delete_message = XInternAtom(xv->display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(xv->display, xv->window, &xv->wm_delete_message, 1);
        XMapWindow(xv->display, xv->window);
    } else
        xv->window = xv->window_id;

    if (XvQueryAdaptors(xv->display, DefaultRootWindow(xv->display), &num_adaptors, &ai) != Success) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }
    if (!num_adaptors) {
        av_log(s, AV_LOG_ERROR, "No X-Video adaptors present\n");
        return AVERROR(ENODEV);
    }
    xv->xv_port = ai[0].base_id;
    XvFreeAdaptorInfo(ai);

    fv = XvListImageFormats(xv->display, xv->xv_port, &num_formats);
    if (!fv) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }
    for (j = 0; j < num_formats; j++) {
        if (fv[j].id == tag) {
            break;
        }
    }
    XFree(fv);

    if (j >= num_formats) {
        av_log(s, AV_LOG_ERROR,
               "Device does not support pixel format %s, aborting\n",
               av_get_pix_fmt_name(par->format));
        ret = AVERROR(EINVAL);
        goto fail;
    }

    xv->gc = XCreateGC(xv->display, xv->window, 0, 0);
    xv->image_width  = par->width;
    xv->image_height = par->height;
    xv->yuv_image = XvShmCreateImage(xv->display, xv->xv_port, tag, 0,
                                     xv->image_width, xv->image_height, &xv->yuv_shminfo);
    xv->yuv_shminfo.shmid = shmget(IPC_PRIVATE, xv->yuv_image->data_size,
                                   IPC_CREAT | 0777);
    xv->yuv_shminfo.shmaddr = (char *)shmat(xv->yuv_shminfo.shmid, 0, 0);
    xv->yuv_image->data = xv->yuv_shminfo.shmaddr;
    xv->yuv_shminfo.readOnly = False;

    XShmAttach(xv->display, &xv->yuv_shminfo);
    XSync(xv->display, False);
    shmctl(xv->yuv_shminfo.shmid, IPC_RMID, 0);

    XGetWindowAttributes(xv->display, xv->window, &window_attrs);
    fgcolor.red = fgcolor.green = fgcolor.blue = 0;
    fgcolor.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(xv->display, window_attrs.colormap, &fgcolor);
    XSetForeground(xv->display, xv->gc, fgcolor.pixel);
    //force display area recalculation at first frame
    xv->window_width = xv->window_height = 0;

    return 0;
  fail:
    xv_write_trailer(s);
    return ret;
}