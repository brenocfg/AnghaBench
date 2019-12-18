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
struct snd_pmac {scalar_t__ model; int subframe; TYPE_1__* awacs; } ;
struct TYPE_2__ {int /*<<< orphan*/  codec_ctrl; } ;

/* Variables and functions */
 int MASK_NEWECMD ; 
 scalar_t__ PMAC_SCREAMER ; 
 int in_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_pmac_screamer_wait (struct snd_pmac*) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 

__attribute__((used)) static void
snd_pmac_awacs_write(struct snd_pmac *chip, int val)
{
	long timeout = 5000000;

	if (chip->model == PMAC_SCREAMER)
		snd_pmac_screamer_wait(chip);
	out_le32(&chip->awacs->codec_ctrl, val | (chip->subframe << 22));
	while (in_le32(&chip->awacs->codec_ctrl) & MASK_NEWECMD) {
		if (! --timeout) {
			snd_printd("snd_pmac_awacs_write timeout\n");
			break;
		}
	}
}