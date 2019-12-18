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
struct work_struct {int dummy; } ;
struct smd_alloc_elm {int /*<<< orphan*/  ctype; int /*<<< orphan*/  cid; int /*<<< orphan*/ * name; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID_CH_ALLOC_TBL ; 
 int /*<<< orphan*/  smd_alloc_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* smd_ch_allocated ; 
 struct smd_alloc_elm* smem_find (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smd_channel_probe_worker(struct work_struct *work)
{
	struct smd_alloc_elm *shared;
	unsigned n;

	shared = smem_find(ID_CH_ALLOC_TBL, sizeof(*shared) * 64);

	for (n = 0; n < 64; n++) {
		if (smd_ch_allocated[n])
			continue;
		if (!shared[n].ref_count)
			continue;
		if (!shared[n].name[0])
			continue;
		smd_alloc_channel(shared[n].name,
				  shared[n].cid,
				  shared[n].ctype);
		smd_ch_allocated[n] = 1;
	}
}