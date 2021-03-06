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
typedef  int /*<<< orphan*/  u32 ;
struct snd_azf3328_codec_data {unsigned int io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  inl (unsigned int) ; 

__attribute__((used)) static inline u32
snd_azf3328_codec_inl(const struct snd_azf3328_codec_data *codec, unsigned reg)
{
	return inl(codec->io_base + reg);
}