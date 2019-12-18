#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  v_texture; int /*<<< orphan*/  u_texture; int /*<<< orphan*/  y_texture; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 

int raspitexutil_create_textures(RASPITEX_STATE *raspitex_state)
{
   GLCHK(glGenTextures(1, &raspitex_state->texture));
   GLCHK(glGenTextures(1, &raspitex_state->y_texture));
   GLCHK(glGenTextures(1, &raspitex_state->u_texture));
   GLCHK(glGenTextures(1, &raspitex_state->v_texture));
   return 0;
}