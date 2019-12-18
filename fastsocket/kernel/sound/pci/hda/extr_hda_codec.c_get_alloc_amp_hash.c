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
struct hda_codec {int /*<<< orphan*/  amp_cache; } ;
struct hda_amp_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_alloc_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hda_amp_info *
get_alloc_amp_hash(struct hda_codec *codec, u32 key)
{
	return (struct hda_amp_info *)get_alloc_hash(&codec->amp_cache, key);
}