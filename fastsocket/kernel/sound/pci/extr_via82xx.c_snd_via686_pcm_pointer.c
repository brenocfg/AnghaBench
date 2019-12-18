#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ addr; } ;
struct viadev {unsigned int tbl_entries; unsigned int lastpos; TYPE_1__ table; } ;
struct via82xx {int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_4__ {struct viadev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_CURR_COUNT ; 
 int /*<<< orphan*/  OFFSET_CURR_PTR ; 
 int /*<<< orphan*/  OFFSET_STATUS ; 
 int /*<<< orphan*/  VIADEV_REG (struct viadev*,int /*<<< orphan*/ ) ; 
 int VIA_REG_STAT_ACTIVE ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_2__*,unsigned int) ; 
 unsigned int calc_linear_pos (struct viadev*,unsigned int,unsigned int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct via82xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_via686_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;
	unsigned int idx, ptr, count, res;

	if (snd_BUG_ON(!viadev->tbl_entries))
		return 0;
	if (!(inb(VIADEV_REG(viadev, OFFSET_STATUS)) & VIA_REG_STAT_ACTIVE))
		return 0;

	spin_lock(&chip->reg_lock);
	count = inl(VIADEV_REG(viadev, OFFSET_CURR_COUNT)) & 0xffffff;
	/* The via686a does not have the current index register,
	 * so we need to calculate the index from CURR_PTR.
	 */
	ptr = inl(VIADEV_REG(viadev, OFFSET_CURR_PTR));
	if (ptr <= (unsigned int)viadev->table.addr)
		idx = 0;
	else /* CURR_PTR holds the address + 8 */
		idx = ((ptr - (unsigned int)viadev->table.addr) / 8 - 1) % viadev->tbl_entries;
	res = calc_linear_pos(viadev, idx, count);
	viadev->lastpos = res; /* remember the last position */
	spin_unlock(&chip->reg_lock);

	return bytes_to_frames(substream->runtime, res);
}