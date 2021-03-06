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
struct snd_soc_codec {int /*<<< orphan*/  reg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8900_REG_RESET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8900_reg_defaults ; 

__attribute__((used)) static void wm8900_reset(struct snd_soc_codec *codec)
{
	snd_soc_write(codec, WM8900_REG_RESET, 0);

	memcpy(codec->reg_cache, wm8900_reg_defaults,
	       sizeof(codec->reg_cache));
}