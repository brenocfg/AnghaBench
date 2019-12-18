#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  image ;
struct TYPE_6__ {int rows; int cols; int /*<<< orphan*/ * vals; } ;
struct TYPE_7__ {int w; int h; TYPE_1__ X; int /*<<< orphan*/  y; scalar_t__ shallow; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ data ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  copy_matrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_to_image (int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ resize_image (int /*<<< orphan*/ ,int,int) ; 

data resize_data(data orig, int w, int h)
{
    data d = {0};
    d.shallow = 0;
    d.w = w;
    d.h = h;
    int i;
    d.X.rows = orig.X.rows;
    d.X.cols = w*h*3;
    d.X.vals = calloc(d.X.rows, sizeof(float*));

    d.y = copy_matrix(orig.y);
#pragma omp parallel for
    for(i = 0; i < orig.X.rows; ++i){
        image im = float_to_image(orig.w, orig.h, 3, orig.X.vals[i]);
        d.X.vals[i] = resize_image(im, w, h).data;
    }
    return d;
}