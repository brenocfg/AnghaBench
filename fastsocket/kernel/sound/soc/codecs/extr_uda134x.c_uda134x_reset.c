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
typedef  int u8 ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDA134X_STATUS0 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int uda134x_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda134x_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void uda134x_reset(struct snd_soc_codec *codec)
{
	u8 reset_reg = uda134x_read_reg_cache(codec, UDA134X_STATUS0);
	uda134x_write(codec, UDA134X_STATUS0, reset_reg | (1<<6));
	msleep(1);
	uda134x_write(codec, UDA134X_STATUS0, reset_reg & ~(1<<6));
}