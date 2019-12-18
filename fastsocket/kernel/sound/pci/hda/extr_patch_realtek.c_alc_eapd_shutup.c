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
 int /*<<< orphan*/  alc_auto_setup_eapd (struct hda_codec*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void alc_eapd_shutup(struct hda_codec *codec)
{
	alc_auto_setup_eapd(codec, false);
	msleep(200);
}