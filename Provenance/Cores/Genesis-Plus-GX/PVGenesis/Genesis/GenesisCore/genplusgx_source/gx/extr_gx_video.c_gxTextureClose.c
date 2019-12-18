#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* data; } ;
typedef  TYPE_1__ gx_texture ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void gxTextureClose(gx_texture **p_texture)
{
  gx_texture *texture = *p_texture;

  if (texture)
  {
    if (texture->data) free(texture->data);
    free(texture);
    *p_texture = NULL;
  }
}