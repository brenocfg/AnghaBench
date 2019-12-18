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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_codec {int /*<<< orphan*/ * reg_cache; } ;

/* Variables and functions */
 int AK4535_CACHEREGNUM ; 
 int ak4535_write (struct snd_soc_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak4535_sync(struct snd_soc_codec *codec)
{
	u16 *cache = codec->reg_cache;
	int i, r = 0;

	for (i = 0; i < AK4535_CACHEREGNUM; i++)
		r |= ak4535_write(codec, i, cache[i]);

	return r;
}