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
struct snd_soc_codec {int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {unsigned int (* read ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 TYPE_1__ soc_ac97_ops ; 
 unsigned int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int ac97_read(struct snd_soc_codec *codec,
	unsigned int reg)
{
	return soc_ac97_ops.read(codec->ac97, reg);
}