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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad1882_3stack_automute (struct hda_codec*) ; 
 int /*<<< orphan*/  ad198x_init (struct hda_codec*) ; 

__attribute__((used)) static int ad1882_3stack_automute_init(struct hda_codec *codec)
{
	ad198x_init(codec);
	ad1882_3stack_automute(codec);
	return 0;
}