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
struct snd_info_entry {int dummy; } ;
struct snd_gf1_mem {int /*<<< orphan*/ * last; int /*<<< orphan*/  first; int /*<<< orphan*/  memory_mutex; } ;
struct TYPE_2__ {scalar_t__ default_voice_address; scalar_t__ enh_mode; int /*<<< orphan*/  memory; struct snd_gf1_mem mem_alloc; } ;
struct snd_gus_card {int /*<<< orphan*/  card; TYPE_1__ gf1; } ;
struct snd_gf1_mem_block {int size; void* name; scalar_t__ ptr; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_GF1_MEM_OWNER_DRIVER ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_gf1_mem_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_gf1_mem_info_read ; 
 int /*<<< orphan*/ * snd_gf1_mem_xalloc (struct snd_gf1_mem*,struct snd_gf1_mem_block*) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_gus_card*,int /*<<< orphan*/ ) ; 

int snd_gf1_mem_init(struct snd_gus_card * gus)
{
	struct snd_gf1_mem *alloc;
	struct snd_gf1_mem_block block;
#ifdef CONFIG_SND_DEBUG
	struct snd_info_entry *entry;
#endif

	alloc = &gus->gf1.mem_alloc;
	mutex_init(&alloc->memory_mutex);
	alloc->first = alloc->last = NULL;
	if (!gus->gf1.memory)
		return 0;

	memset(&block, 0, sizeof(block));
	block.owner = SNDRV_GF1_MEM_OWNER_DRIVER;
	if (gus->gf1.enh_mode) {
		block.ptr = 0;
		block.size = 1024;
		block.name = kstrdup("InterWave LFOs", GFP_KERNEL);
		if (snd_gf1_mem_xalloc(alloc, &block) == NULL)
			return -ENOMEM;
	}
	block.ptr = gus->gf1.default_voice_address;
	block.size = 4;
	block.name = kstrdup("Voice default (NULL's)", GFP_KERNEL);
	if (snd_gf1_mem_xalloc(alloc, &block) == NULL)
		return -ENOMEM;
#ifdef CONFIG_SND_DEBUG
	if (! snd_card_proc_new(gus->card, "gusmem", &entry))
		snd_info_set_text_ops(entry, gus, snd_gf1_mem_info_read);
#endif
	return 0;
}