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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__* data; int /*<<< orphan*/ * linesize; } ;
typedef  int /*<<< orphan*/  CDXLVideoContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  import_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  import_palette (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdxl_decode_rgb(CDXLVideoContext *c, AVFrame *frame)
{
    uint32_t *new_palette = (uint32_t *)frame->data[1];

    memset(frame->data[1], 0, AVPALETTE_SIZE);
    import_palette(c, new_palette);
    import_format(c, frame->linesize[0], frame->data[0]);
}