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
struct bttv {int /*<<< orphan*/  mute; } ;

/* Variables and functions */
 int audio_mux (struct bttv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
audio_input(struct bttv *btv, int input)
{
	return audio_mux(btv, input, btv->mute);
}