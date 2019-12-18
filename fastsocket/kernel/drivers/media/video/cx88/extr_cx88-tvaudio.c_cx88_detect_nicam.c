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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_NICAM_STATUS2 ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cx88_detect_nicam(struct cx88_core *core)
{
	int i, j = 0;

	dprintk("start nicam autodetect.\n");

	for (i = 0; i < 6; i++) {
		/* if bit1=1 then nicam is detected */
		j += ((cx_read(AUD_NICAM_STATUS2) & 0x02) >> 1);

		if (j == 1) {
			dprintk("nicam is detected.\n");
			return 1;
		}

		/* wait a little bit for next reading status */
		msleep(10);
	}

	dprintk("nicam is not detected.\n");
	return 0;
}