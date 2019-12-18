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
struct ct_mixer {struct ct_mixer* amixers; void* sums; } ;

/* Variables and functions */
 int CHN_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_CT_AMIXERS ; 
 int NUM_CT_SUMS ; 
 int /*<<< orphan*/  kfree (struct ct_mixer*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_mixer_get_mem(struct ct_mixer **rmixer)
{
	struct ct_mixer *mixer;
	int err;

	*rmixer = NULL;
	/* Allocate mem for mixer obj */
	mixer = kzalloc(sizeof(*mixer), GFP_KERNEL);
	if (!mixer)
		return -ENOMEM;

	mixer->amixers = kzalloc(sizeof(void *)*(NUM_CT_AMIXERS*CHN_NUM),
				 GFP_KERNEL);
	if (!mixer->amixers) {
		err = -ENOMEM;
		goto error1;
	}
	mixer->sums = kzalloc(sizeof(void *)*(NUM_CT_SUMS*CHN_NUM), GFP_KERNEL);
	if (!mixer->sums) {
		err = -ENOMEM;
		goto error2;
	}

	*rmixer = mixer;
	return 0;

error2:
	kfree(mixer->amixers);
error1:
	kfree(mixer);
	return err;
}