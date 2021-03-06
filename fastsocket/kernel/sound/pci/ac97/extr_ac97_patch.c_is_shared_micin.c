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
struct snd_ac97 {int /*<<< orphan*/  indep_surround; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_clfe_on (struct snd_ac97*) ; 

__attribute__((used)) static inline int is_shared_micin(struct snd_ac97 *ac97)
{
	return !ac97->indep_surround && !is_clfe_on(ac97);
}