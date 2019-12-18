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
typedef  size_t int16_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int SUBL ; 
 int /*<<< orphan*/  add_vector_and_shift (size_t*,size_t*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alpha ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  vector_multiplication (size_t*,size_t*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vector_rmultiplication (size_t*,size_t*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void create_augmented_vector(int index, int16_t *buffer, int16_t *cbVec)
{
    int16_t cbVecTmp[4];
    int interpolation_length = FFMIN(4, index);
    int16_t ilow = index - interpolation_length;

    memcpy(cbVec, buffer - index, index * 2);

    vector_multiplication(&cbVec[ilow], buffer - index - interpolation_length, alpha, interpolation_length, 15);
    vector_rmultiplication(cbVecTmp, buffer - interpolation_length, &alpha[interpolation_length - 1], interpolation_length, 15);
    add_vector_and_shift(&cbVec[ilow], &cbVec[ilow], cbVecTmp, interpolation_length, 0);

    memcpy(cbVec + index, buffer - index, FFMIN(SUBL - index, index) * sizeof(*cbVec));
}