#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int win_x; int win_y; } ;
typedef  TYPE_1__ xcb_query_pointer_reply_t ;
struct TYPE_9__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_2__ xcb_get_geometry_reply_t ;
struct TYPE_10__ {int x; int y; int width; int height; int follow_mouse; } ;
typedef  TYPE_3__ XCBGrabContext ;
struct TYPE_11__ {TYPE_3__* priv_data; } ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int) ; 
 void* FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int FOLLOW_CENTER ; 

__attribute__((used)) static int xcbgrab_reposition(AVFormatContext *s,
                              xcb_query_pointer_reply_t *p,
                              xcb_get_geometry_reply_t *geo)
{
    XCBGrabContext *c = s->priv_data;
    int x = c->x, y = c->y;
    int w = c->width, h = c->height, f = c->follow_mouse;
    int p_x, p_y;

    if (!p || !geo)
        return AVERROR(EIO);

    p_x = p->win_x;
    p_y = p->win_y;

    if (f == FOLLOW_CENTER) {
        x = p_x - w / 2;
        y = p_y - h / 2;
    } else {
        int left   = x + f;
        int right  = x + w - f;
        int top    = y + f;
        int bottom = y + h - f;
        if (p_x > right) {
            x += p_x - right;
        } else if (p_x < left) {
            x -= left - p_x;
        }
        if (p_y > bottom) {
            y += p_y - bottom;
        } else if (p_y < top) {
            y -= top - p_y;
        }
    }

    c->x = FFMIN(FFMAX(0, x), geo->width  - w);
    c->y = FFMIN(FFMAX(0, y), geo->height - h);

    return 0;
}