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
typedef  int /*<<< orphan*/  RASPITEX_STATE ;
typedef  int GLfloat ;

/* Variables and functions */
 int angle ; 
 int anim_step ; 

__attribute__((used)) static int square_update_model(RASPITEX_STATE *state)
{
   int frames_per_rev = 30 * 15;
   (void) state;
   angle = (anim_step * 360) / (GLfloat) frames_per_rev;
   anim_step = (anim_step + 1) % frames_per_rev;

   return 0;
}