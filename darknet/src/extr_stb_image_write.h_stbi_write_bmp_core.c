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
typedef  int /*<<< orphan*/  stbi__write_context ;

/* Variables and functions */
 int stbiw__outfile (int /*<<< orphan*/ *,int,int,int,int,int,int,void*,int /*<<< orphan*/ ,int,char*,char,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stbi_write_bmp_core(stbi__write_context *s, int x, int y, int comp, const void *data)
{
   int pad = (-x*3) & 3;
   return stbiw__outfile(s,-1,-1,x,y,comp,1,(void *) data,0,pad,
           "11 4 22 4" "4 44 22 444444",
           'B', 'M', 14+40+(x*3+pad)*y, 0,0, 14+40,  // file header
            40, x,y, 1,24, 0,0,0,0,0,0);             // bitmap header
}