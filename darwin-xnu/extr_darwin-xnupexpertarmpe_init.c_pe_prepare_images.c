#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int v_rotate; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_5__ {int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 TYPE_3__ PE_state ; 
 TYPE_2__ default_progress ; 

__attribute__((used)) static void
pe_prepare_images(void)
{
	if ((1 & PE_state.video.v_rotate) != 0) {
		// Only square square images with radial symmetry are supported
		// No need to actually rotate the data

		// Swap the dx and dy offsets
		uint32_t tmp = default_progress.dx;
		default_progress.dx = default_progress.dy;
		default_progress.dy = tmp;
	}
#if 0
	uint32_t cnt, cnt2, cnt3, cnt4;
	uint32_t tmp, width, height;
	uint8_t  data, *new_data;
	const uint8_t *old_data;

	width  = default_progress.width;
	height = default_progress.height * default_progress.count;

	// Scale images if the UI is being scaled
	if (PE_state.video.v_scale > 1) {
		new_data = kalloc(width * height * scale * scale);
		if (new_data != 0) {
			old_data = default_progress_data;
			default_progress_data = new_data;
			for (cnt = 0; cnt < height; cnt++) {
				for (cnt2 = 0; cnt2 < width; cnt2++) {
					data = *(old_data++);
					for (cnt3 = 0; cnt3 < scale; cnt3++) {
						for (cnt4 = 0; cnt4 < scale; cnt4++) {
							new_data[width * scale * cnt3 + cnt4] = data;
						}
					}
					new_data += scale;
				}
				new_data += width * scale * (scale - 1);
			}
			default_progress.width  *= scale;
			default_progress.height *= scale;
			default_progress.dx     *= scale;
			default_progress.dy     *= scale;
		}
	}
#endif
}