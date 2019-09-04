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

/* Variables and functions */
 int PI ; 
 int /*<<< orphan*/  mat_identity (float*) ; 
 int /*<<< orphan*/  mat_multiply (float*,float*,float*) ; 
 int /*<<< orphan*/  mat_ortho (float*,float,float,float,float,int,int) ; 
 int /*<<< orphan*/  mat_rotate (float*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mat_translate (float*,float,float,int /*<<< orphan*/ ) ; 

void set_matrix_item(float *matrix, int width, int height, int scale) {
    float a[16];
    float b[16];
    float aspect = (float)width / height;
    float size = 64 * scale;
    float box = height / size / 2;
    float xoffset = 1 - size / width * 2;
    float yoffset = 1 - size / height * 2;
    mat_identity(a);
    mat_rotate(b, 0, 1, 0, -PI / 4);
    mat_multiply(a, b, a);
    mat_rotate(b, 1, 0, 0, -PI / 10);
    mat_multiply(a, b, a);
    mat_ortho(b, -box * aspect, box * aspect, -box, box, -1, 1);
    mat_multiply(a, b, a);
    mat_translate(b, -xoffset, -yoffset, 0);
    mat_multiply(a, b, a);
    mat_identity(matrix);
    mat_multiply(matrix, a, matrix);
}