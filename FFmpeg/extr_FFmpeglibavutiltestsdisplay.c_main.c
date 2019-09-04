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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_display_matrix_flip (int /*<<< orphan*/ *,int,int) ; 
 double av_display_rotation_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_display_rotation_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_matrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

int main(void)
{
    int32_t matrix[9];

    // Set the matrix to 90 degrees
    av_display_rotation_set(matrix, 90);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // Set the matrix to -45 degrees
    av_display_rotation_set(matrix, -45);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // flip horizontal
    av_display_matrix_flip(matrix, 1, 0);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    // flip vertical
    av_display_matrix_flip(matrix, 0, 1);
    print_matrix(matrix);
    printf("degrees: %f\n", av_display_rotation_get(matrix));

    return 0;

}