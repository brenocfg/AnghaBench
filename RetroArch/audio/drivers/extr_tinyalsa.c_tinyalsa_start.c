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
struct TYPE_2__ {int is_paused; int /*<<< orphan*/  pcm; scalar_t__ can_pause; } ;
typedef  TYPE_1__ tinyalsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int pcm_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tinyalsa_start(void *data, bool is_shutdown)
{
	tinyalsa_t *tinyalsa = (tinyalsa_t*)data;

	if (tinyalsa->can_pause && tinyalsa->is_paused)
   {
		int ret = pcm_pause(tinyalsa->pcm, 0);

		if (ret < 0)
      {
			RARCH_ERR("[TINYALSA]: Failed to unpause.\n");
			return false;
		}

		tinyalsa->is_paused = false;
	}

	return true;
}