#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_APP_TO_DEV_WINDOW_REPAINT 128 
 int /*<<< orphan*/  ENOSYS ; 
 int xv_repaint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xv_control_message(AVFormatContext *s, int type, void *data, size_t data_size)
{
    switch(type) {
    case AV_APP_TO_DEV_WINDOW_REPAINT:
        return xv_repaint(s);
    default:
        break;
    }
    return AVERROR(ENOSYS);
}