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
 int /*<<< orphan*/  conexant_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5047_hp_automute (struct hda_codec*) ; 

__attribute__((used)) static int cxt5047_hp_init(struct hda_codec *codec)
{
	conexant_init(codec);
	cxt5047_hp_automute(codec);
	return 0;
}