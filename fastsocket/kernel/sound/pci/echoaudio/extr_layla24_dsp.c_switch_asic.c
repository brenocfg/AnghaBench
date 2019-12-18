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
struct firmware {int dummy; } ;
struct echoaudio {TYPE_1__* comm_page; struct firmware const* asic_code; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_2__ {int /*<<< orphan*/  monitors; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_FNC_LOAD_LAYLA24_EXTERNAL_ASIC ; 
 int /*<<< orphan*/  ECHOGAIN_MUTED ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MONITOR_ARRAY_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ load_asic_generic (struct echoaudio*,int /*<<< orphan*/ ,struct firmware const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int switch_asic(struct echoaudio *chip, const struct firmware *asic)
{
	s8 *monitors;

	/*  Check to see if this is already loaded */
	if (asic != chip->asic_code) {
		monitors = kmemdup(chip->comm_page->monitors,
					MONITOR_ARRAY_SIZE, GFP_KERNEL);
		if (! monitors)
			return -ENOMEM;

		memset(chip->comm_page->monitors, ECHOGAIN_MUTED,
		       MONITOR_ARRAY_SIZE);

		/* Load the desired ASIC */
		if (load_asic_generic(chip, DSP_FNC_LOAD_LAYLA24_EXTERNAL_ASIC,
				      asic) < 0) {
			memcpy(chip->comm_page->monitors, monitors,
			       MONITOR_ARRAY_SIZE);
			kfree(monitors);
			return -EIO;
		}
		chip->asic_code = asic;
		memcpy(chip->comm_page->monitors, monitors, MONITOR_ARRAY_SIZE);
		kfree(monitors);
	}

	return 0;
}