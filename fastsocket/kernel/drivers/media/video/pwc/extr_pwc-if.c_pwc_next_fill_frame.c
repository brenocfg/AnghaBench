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
struct pwc_device {int /*<<< orphan*/  ptrlock; TYPE_1__* fill_frame; TYPE_1__* full_frames; TYPE_1__* empty_frames; TYPE_1__* full_frames_tail; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PWC_ERROR (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pwc_next_fill_frame(struct pwc_device *pdev)
{
	int ret;
	unsigned long flags;

	ret = 0;
	spin_lock_irqsave(&pdev->ptrlock, flags);
	if (pdev->fill_frame != NULL) {
		/* append to 'full' list */
		if (pdev->full_frames == NULL) {
			pdev->full_frames = pdev->fill_frame;
			pdev->full_frames_tail = pdev->full_frames;
		}
		else {
			pdev->full_frames_tail->next = pdev->fill_frame;
			pdev->full_frames_tail = pdev->fill_frame;
		}
	}
	if (pdev->empty_frames != NULL) {
		/* We have empty frames available. That's easy */
		pdev->fill_frame = pdev->empty_frames;
		pdev->empty_frames = pdev->empty_frames->next;
	}
	else {
		/* Hmm. Take it from the full list */
		/* sanity check */
		if (pdev->full_frames == NULL) {
			PWC_ERROR("Neither empty or full frames available!\n");
			spin_unlock_irqrestore(&pdev->ptrlock, flags);
			return -EINVAL;
		}
		pdev->fill_frame = pdev->full_frames;
		pdev->full_frames = pdev->full_frames->next;
		ret = 1;
	}
	pdev->fill_frame->next = NULL;
	spin_unlock_irqrestore(&pdev->ptrlock, flags);
	return ret;
}