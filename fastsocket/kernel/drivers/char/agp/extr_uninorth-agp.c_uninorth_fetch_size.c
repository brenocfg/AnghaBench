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
struct aper_size_info_32 {int size; } ;
struct TYPE_6__ {int aperture_size_idx; void* current_size; void* previous_size; TYPE_2__* driver; TYPE_1__* dev; } ;
struct TYPE_5__ {int num_aperture_sizes; int /*<<< orphan*/  aperture_sizes; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct aper_size_info_32* A_SIZE_32 (int /*<<< orphan*/ ) ; 
 int DEFAULT_APERTURE_SIZE ; 
 TYPE_3__* agp_bridge ; 
 char* aperture ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int memparse (char*,char**) ; 

__attribute__((used)) static int uninorth_fetch_size(void)
{
	int i, size = 0;
	struct aper_size_info_32 *values =
	    A_SIZE_32(agp_bridge->driver->aperture_sizes);

	if (aperture) {
		char *save = aperture;

		size = memparse(aperture, &aperture) >> 20;
		aperture = save;

		for (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++)
			if (size == values[i].size)
				break;

		if (i == agp_bridge->driver->num_aperture_sizes) {
			dev_err(&agp_bridge->dev->dev, "invalid aperture size, "
				"using default\n");
			size = 0;
			aperture = NULL;
		}
	}

	if (!size) {
		for (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++)
			if (values[i].size == DEFAULT_APERTURE_SIZE)
				break;
	}

	agp_bridge->previous_size =
	    agp_bridge->current_size = (void *)(values + i);
	agp_bridge->aperture_size_idx = i;
	return values[i].size;
}