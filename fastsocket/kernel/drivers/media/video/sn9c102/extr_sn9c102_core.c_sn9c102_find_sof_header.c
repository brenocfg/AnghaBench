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
struct TYPE_2__ {int bytesread; char* header; } ;
struct sn9c102_device {TYPE_1__ sof; } ;
typedef  int /*<<< orphan*/  marker ;

/* Variables and functions */
 int /*<<< orphan*/  PDBGG (char*,size_t,size_t) ; 
 size_t sn9c102_sof_length (struct sn9c102_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void*
sn9c102_find_sof_header(struct sn9c102_device* cam, void* mem, size_t len)
{
	static const char marker[6] = {0xff, 0xff, 0x00, 0xc4, 0xc4, 0x96};
	const char *m = mem;
	size_t soflen = 0, i, j;

	soflen = sn9c102_sof_length(cam);

	for (i = 0; i < len; i++) {
		size_t b;

		/* Read the variable part of the header */
		if (unlikely(cam->sof.bytesread >= sizeof(marker))) {
			cam->sof.header[cam->sof.bytesread] = *(m+i);
			if (++cam->sof.bytesread == soflen) {
				cam->sof.bytesread = 0;
				return mem + i;
			}
			continue;
		}

		/* Search for the SOF marker (fixed part) in the header */
		for (j = 0, b=cam->sof.bytesread; j+b < sizeof(marker); j++) {
			if (unlikely(i+j == len))
				return NULL;
			if (*(m+i+j) == marker[cam->sof.bytesread]) {
				cam->sof.header[cam->sof.bytesread] = *(m+i+j);
				if (++cam->sof.bytesread == sizeof(marker)) {
					PDBGG("Bytes to analyze: %zd. SOF "
					      "starts at byte #%zd", len, i);
					i += j+1;
					break;
				}
			} else {
				cam->sof.bytesread = 0;
				break;
			}
		}
	}

	return NULL;
}