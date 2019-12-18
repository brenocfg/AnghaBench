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
typedef  int u32 ;
typedef  float f32 ;
typedef  float** MtxP ;
typedef  float** Mtx ;

/* Variables and functions */
 int /*<<< orphan*/  c_guMtxCopy (float**,float**) ; 

u32 c_guMtxInvXpose(Mtx src, Mtx xPose)
{
    Mtx mTmp;
    MtxP m;
    f32 det;

    if(src == xPose)
        m = mTmp;
    else
        m = xPose;

    // Compute the determinant of the upper 3x3 submatrix
    det =   src[0][0]*src[1][1]*src[2][2] + src[0][1]*src[1][2]*src[2][0] + src[0][2]*src[1][0]*src[2][1]
          - src[2][0]*src[1][1]*src[0][2] - src[1][0]*src[0][1]*src[2][2] - src[0][0]*src[2][1]*src[1][2];

    // Check if matrix is singular
    if(det == 0.0f) return 0;

    // Compute the inverse of the upper submatrix:

    // Find the transposed matrix of cofactors of the upper submatrix
    // and multiply by (1/det)

    det = 1.0f / det;

    m[0][0] =  (src[1][1]*src[2][2] - src[2][1]*src[1][2]) * det;
    m[0][1] = -(src[1][0]*src[2][2] - src[2][0]*src[1][2]) * det;
    m[0][2] =  (src[1][0]*src[2][1] - src[2][0]*src[1][1]) * det;

    m[1][0] = -(src[0][1]*src[2][2] - src[2][1]*src[0][2]) * det;
    m[1][1] =  (src[0][0]*src[2][2] - src[2][0]*src[0][2]) * det;
    m[1][2] = -(src[0][0]*src[2][1] - src[2][0]*src[0][1]) * det;

    m[2][0] =  (src[0][1]*src[1][2] - src[1][1]*src[0][2]) * det;
    m[2][1] = -(src[0][0]*src[1][2] - src[1][0]*src[0][2]) * det;
    m[2][2] =  (src[0][0]*src[1][1] - src[1][0]*src[0][1]) * det;

    // The 4th columns should be zero
    m[0][3] = 0.0F;
    m[1][3] = 0.0F;
    m[2][3] = 0.0F;

    // Copy back if needed
    if(m == mTmp)
        c_guMtxCopy(mTmp, xPose);

    return 1;
}