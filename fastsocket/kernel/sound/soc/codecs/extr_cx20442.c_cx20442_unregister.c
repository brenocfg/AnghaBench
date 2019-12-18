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
struct cx20442_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cx20442_codec ; 
 int /*<<< orphan*/  cx20442_dai ; 
 int /*<<< orphan*/  kfree (struct cx20442_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx20442_unregister(struct cx20442_priv *cx20442)
{
	snd_soc_unregister_dai(&cx20442_dai);
	snd_soc_unregister_codec(&cx20442->codec);

	cx20442_codec = NULL;
	kfree(cx20442);
}