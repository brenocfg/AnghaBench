#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ readpos; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int inserted_frame; TYPE_2__ sliced_mpeg_buf; int /*<<< orphan*/ * sliced_mpeg_size; int /*<<< orphan*/ * sliced_mpeg_data; } ;
struct ivtv {TYPE_1__ vbi; } ;

/* Variables and functions */
 int IVTV_VBI_FRAMES ; 

__attribute__((used)) static void ivtv_setup_sliced_vbi_buf(struct ivtv *itv)
{
	int idx = itv->vbi.inserted_frame % IVTV_VBI_FRAMES;

	itv->vbi.sliced_mpeg_buf.buf = itv->vbi.sliced_mpeg_data[idx];
	itv->vbi.sliced_mpeg_buf.bytesused = itv->vbi.sliced_mpeg_size[idx];
	itv->vbi.sliced_mpeg_buf.readpos = 0;
}