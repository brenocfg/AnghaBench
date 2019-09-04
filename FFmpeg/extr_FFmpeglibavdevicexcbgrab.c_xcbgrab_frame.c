#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_get_image_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_image_cookie_t ;
struct TYPE_12__ {int /*<<< orphan*/  major_code; int /*<<< orphan*/  minor_code; int /*<<< orphan*/  resource_id; int /*<<< orphan*/  sequence; int /*<<< orphan*/  error_code; int /*<<< orphan*/  response_type; } ;
typedef  TYPE_2__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_1__* screen; } ;
typedef  TYPE_3__ XCBGrabContext ;
struct TYPE_15__ {TYPE_3__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  XCB_IMAGE_FORMAT_Z_PIXMAP ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_new_packet (TYPE_4__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xcb_get_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_get_image_data (int /*<<< orphan*/ *) ; 
 int xcb_get_image_data_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_get_image_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 

__attribute__((used)) static int xcbgrab_frame(AVFormatContext *s, AVPacket *pkt)
{
    XCBGrabContext *c = s->priv_data;
    xcb_get_image_cookie_t iq;
    xcb_get_image_reply_t *img;
    xcb_drawable_t drawable = c->screen->root;
    xcb_generic_error_t *e = NULL;
    uint8_t *data;
    int length, ret;

    iq  = xcb_get_image(c->conn, XCB_IMAGE_FORMAT_Z_PIXMAP, drawable,
                        c->x, c->y, c->width, c->height, ~0);

    img = xcb_get_image_reply(c->conn, iq, &e);

    if (e) {
        av_log(s, AV_LOG_ERROR,
               "Cannot get the image data "
               "event_error: response_type:%u error_code:%u "
               "sequence:%u resource_id:%u minor_code:%u major_code:%u.\n",
               e->response_type, e->error_code,
               e->sequence, e->resource_id, e->minor_code, e->major_code);
        return AVERROR(EACCES);
    }

    if (!img)
        return AVERROR(EAGAIN);

    data   = xcb_get_image_data(img);
    length = xcb_get_image_data_length(img);

    ret = av_new_packet(pkt, length);

    if (!ret)
        memcpy(pkt->data, data, length);

    free(img);

    return ret;
}