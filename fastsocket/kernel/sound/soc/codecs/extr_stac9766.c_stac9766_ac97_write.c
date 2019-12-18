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
typedef  unsigned int u16 ;
struct snd_soc_codec {unsigned int* reg_cache; int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 unsigned int AC97_INT_PAGING ; 
 unsigned int AC97_STAC_PAGE0 ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 TYPE_1__ soc_ac97_ops ; 
 int /*<<< orphan*/  stac9766_reg ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int stac9766_ac97_write(struct snd_soc_codec *codec, unsigned int reg,
			       unsigned int val)
{
	u16 *cache = codec->reg_cache;

	if (reg > AC97_STAC_PAGE0) {
		stac9766_ac97_write(codec, AC97_INT_PAGING, 0);
		soc_ac97_ops.write(codec->ac97, reg, val);
		stac9766_ac97_write(codec, AC97_INT_PAGING, 1);
		return 0;
	}
	if (reg / 2 >= ARRAY_SIZE(stac9766_reg))
		return -EIO;

	soc_ac97_ops.write(codec->ac97, reg, val);
	cache[reg / 2] = val;
	return 0;
}