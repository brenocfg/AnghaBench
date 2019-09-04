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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void WKdm_hv(uint32_t *wkbuf) {
#if DEVELOPMENT || DEBUG
	uint32_t *inw = (uint32_t *) wkbuf;
	if (*inw != MZV_MAGIC) {
		if ((*inw | *(inw + 1) | *(inw + 2)) & 0xFFFF0000) {
			panic("WKdm(%p): invalid header 0x%x 0x%x 0x%x\n", wkbuf, *inw, *(inw +1), *(inw+2));
		}
	}
#else /* DEVELOPMENT || DEBUG */
	(void) wkbuf;
#endif
}