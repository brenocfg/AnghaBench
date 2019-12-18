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
struct ad1836_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ad1836_codec ; 
 int /*<<< orphan*/  ad1836_dai ; 
 int /*<<< orphan*/  kfree (struct ad1836_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad1836_unregister(struct ad1836_priv *ad1836)
{
	snd_soc_unregister_dai(&ad1836_dai);
	snd_soc_unregister_codec(&ad1836->codec);
	kfree(ad1836);
	ad1836_codec = NULL;
}