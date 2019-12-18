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
typedef  int /*<<< orphan*/  GSTEXTURE ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

__attribute__((used)) static GSTEXTURE * prepare_new_texture(void)
{
   GSTEXTURE *texture = calloc(1, sizeof(*texture));
   return texture;
}