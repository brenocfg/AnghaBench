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
struct TYPE_3__ {float w; float h; int /*<<< orphan*/  texture; } ;
typedef  TYPE_1__ Texture ;

/* Variables and functions */
 int /*<<< orphan*/  fill_textured_rectangle (float,float,float,float,float,float,float,float,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_or_cache_url (char const*) ; 

void fill_image(float x0, float y0, float scale, float r, float g, float b, float a, const char *url)
{
  Texture *t = find_or_cache_url(url);
  fill_textured_rectangle(x0, y0, x0 + t->w * scale, y0 + t->h * scale, r, g, b, a, t->texture);
}