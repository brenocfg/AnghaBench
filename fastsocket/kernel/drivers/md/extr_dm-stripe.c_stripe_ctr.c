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
typedef  int uint32_t ;
struct stripe_c {int stripes; int stripes_shift; int chunk_size; int chunk_size_shift; TYPE_1__* stripe; int /*<<< orphan*/  stripe_width; struct dm_target* ti; int /*<<< orphan*/  kstriped_ws; } ;
struct dm_target {char* error; int num_flush_requests; int num_discard_requests; struct stripe_c* private; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  error_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* __ffs (int) ; 
 struct stripe_c* alloc_context (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int dm_set_target_max_io_len (struct dm_target*,int) ; 
 int get_stripe (struct dm_target*,struct stripe_c*,unsigned int,char**) ; 
 int /*<<< orphan*/  kfree (struct stripe_c*) ; 
 scalar_t__ kstrtouint (char*,int,int*) ; 
 scalar_t__ sector_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trigger_event ; 

__attribute__((used)) static int stripe_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct stripe_c *sc;
	sector_t width, tmp_len;
	uint32_t stripes;
	uint32_t chunk_size;
	int r;
	unsigned int i;

	if (argc < 2) {
		ti->error = "Not enough arguments";
		return -EINVAL;
	}

	if (kstrtouint(argv[0], 10, &stripes) || !stripes) {
		ti->error = "Invalid stripe count";
		return -EINVAL;
	}

	if (kstrtouint(argv[1], 10, &chunk_size) || !chunk_size) {
		ti->error = "Invalid chunk_size";
		return -EINVAL;
	}

	width = ti->len;
	if (sector_div(width, stripes)) {
		ti->error = "Target length not divisible by "
		    "number of stripes";
		return -EINVAL;
	}

	tmp_len = width;
	if (sector_div(tmp_len, chunk_size)) {
		ti->error = "Target length not divisible by "
		    "chunk size";
		return -EINVAL;
	}

	/*
	 * Do we have enough arguments for that many stripes ?
	 */
	if (argc != (2 + 2 * stripes)) {
		ti->error = "Not enough destinations "
			"specified";
		return -EINVAL;
	}

	sc = alloc_context(stripes);
	if (!sc) {
		ti->error = "Memory allocation for striped context "
		    "failed";
		return -ENOMEM;
	}

	INIT_WORK(&sc->kstriped_ws, trigger_event);

	/* Set pointer to dm target; used in trigger_event */
	sc->ti = ti;
	sc->stripes = stripes;
	sc->stripe_width = width;

	if (stripes & (stripes - 1))
		sc->stripes_shift = -1;
	else
		sc->stripes_shift = __ffs(stripes);

	r = dm_set_target_max_io_len(ti, chunk_size);
	if (r)
		return r;

	ti->num_flush_requests = stripes;
	ti->num_discard_requests = stripes;

	sc->chunk_size = chunk_size;
	if (chunk_size & (chunk_size - 1))
		sc->chunk_size_shift = -1;
	else
		sc->chunk_size_shift = __ffs(chunk_size);

	/*
	 * Get the stripe destinations.
	 */
	for (i = 0; i < stripes; i++) {
		argv += 2;

		r = get_stripe(ti, sc, i, argv);
		if (r < 0) {
			ti->error = "Couldn't parse stripe destination";
			while (i--)
				dm_put_device(ti, sc->stripe[i].dev);
			kfree(sc);
			return r;
		}
		atomic_set(&(sc->stripe[i].error_count), 0);
	}

	ti->private = sc;

	return 0;
}