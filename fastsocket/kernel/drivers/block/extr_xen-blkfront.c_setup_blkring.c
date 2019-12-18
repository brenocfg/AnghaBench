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
struct xenbus_device {int dummy; } ;
struct blkif_sring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct blkfront_info {int ring_ref; int irq; int /*<<< orphan*/  evtchn; TYPE_1__ ring; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,struct blkif_sring*,int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 int GRANT_INVALID_REF ; 
 int /*<<< orphan*/  IRQF_SAMPLE_RANDOM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SHARED_RING_INIT (struct blkif_sring*) ; 
 int __GFP_HIGH ; 
 scalar_t__ __get_free_page (int) ; 
 int bind_evtchn_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct blkfront_info*) ; 
 int /*<<< orphan*/  blkif_free (struct blkfront_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkif_interrupt ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_mfn (int /*<<< orphan*/ *) ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_grant_ring (struct xenbus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_blkring(struct xenbus_device *dev,
			 struct blkfront_info *info)
{
	struct blkif_sring *sring;
	int err;

	info->ring_ref = GRANT_INVALID_REF;

	sring = (struct blkif_sring *)__get_free_page(GFP_NOIO | __GFP_HIGH);
	if (!sring) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating shared ring");
		return -ENOMEM;
	}
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&info->ring, sring, PAGE_SIZE);

	sg_init_table(info->sg, BLKIF_MAX_SEGMENTS_PER_REQUEST);

	err = xenbus_grant_ring(dev, virt_to_mfn(info->ring.sring));
	if (err < 0) {
		free_page((unsigned long)sring);
		info->ring.sring = NULL;
		goto fail;
	}
	info->ring_ref = err;

	err = xenbus_alloc_evtchn(dev, &info->evtchn);
	if (err)
		goto fail;

	err = bind_evtchn_to_irqhandler(info->evtchn,
					blkif_interrupt,
					IRQF_SAMPLE_RANDOM, "blkif", info);
	if (err <= 0) {
		xenbus_dev_fatal(dev, err,
				 "bind_evtchn_to_irqhandler failed");
		goto fail;
	}
	info->irq = err;

	return 0;
fail:
	blkif_free(info, 0);
	return err;
}