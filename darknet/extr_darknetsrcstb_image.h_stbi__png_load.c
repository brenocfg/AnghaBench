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
typedef  int /*<<< orphan*/  stbi__result_info ;
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ stbi__png ;
typedef  int /*<<< orphan*/  stbi__context ;

/* Variables and functions */
 void* stbi__do_png (TYPE_1__*,int*,int*,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *stbi__png_load(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri)
{
   stbi__png p;
   p.s = s;
   return stbi__do_png(&p, x,y,comp,req_comp, ri);
}