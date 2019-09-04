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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  ulti_convert_yuv (int /*<<< orphan*/ *,int,int,int*,int) ; 

__attribute__((used)) static void ulti_grad(AVFrame *frame, int x, int y, uint8_t *Y, int chroma, int angle)
{
    uint8_t Luma[16];
    if(angle & 8) { //reverse order
        int t;
        angle &= 0x7;
        t = Y[0];
        Y[0] = Y[3];
        Y[3] = t;
        t = Y[1];
        Y[1] = Y[2];
        Y[2] = t;
    }
    switch(angle){
    case 0:
        Luma[0]  = Y[0]; Luma[1]  = Y[1]; Luma[2]  = Y[2]; Luma[3]  = Y[3];
        Luma[4]  = Y[0]; Luma[5]  = Y[1]; Luma[6]  = Y[2]; Luma[7]  = Y[3];
        Luma[8]  = Y[0]; Luma[9]  = Y[1]; Luma[10] = Y[2]; Luma[11] = Y[3];
        Luma[12] = Y[0]; Luma[13] = Y[1]; Luma[14] = Y[2]; Luma[15] = Y[3];
        break;
    case 1:
        Luma[0]  = Y[1]; Luma[1]  = Y[2]; Luma[2]  = Y[3]; Luma[3]  = Y[3];
        Luma[4]  = Y[0]; Luma[5]  = Y[1]; Luma[6]  = Y[2]; Luma[7]  = Y[3];
        Luma[8]  = Y[0]; Luma[9]  = Y[1]; Luma[10] = Y[2]; Luma[11] = Y[3];
        Luma[12] = Y[0]; Luma[13] = Y[0]; Luma[14] = Y[1]; Luma[15] = Y[2];
        break;
    case 2:
        Luma[0]  = Y[1]; Luma[1]  = Y[2]; Luma[2]  = Y[3]; Luma[3]  = Y[3];
        Luma[4]  = Y[1]; Luma[5]  = Y[2]; Luma[6]  = Y[2]; Luma[7]  = Y[3];
        Luma[8]  = Y[0]; Luma[9]  = Y[1]; Luma[10] = Y[1]; Luma[11] = Y[2];
        Luma[12] = Y[0]; Luma[13] = Y[0]; Luma[14] = Y[1]; Luma[15] = Y[2];
        break;
    case 3:
        Luma[0]  = Y[2]; Luma[1]  = Y[3]; Luma[2]  = Y[3]; Luma[3]  = Y[3];
        Luma[4]  = Y[1]; Luma[5]  = Y[2]; Luma[6]  = Y[2]; Luma[7]  = Y[3];
        Luma[8]  = Y[0]; Luma[9]  = Y[1]; Luma[10] = Y[1]; Luma[11] = Y[2];
        Luma[12] = Y[0]; Luma[13] = Y[0]; Luma[14] = Y[0]; Luma[15] = Y[1];
        break;
    case 4:
        Luma[0]  = Y[3]; Luma[1]  = Y[3]; Luma[2]  = Y[3]; Luma[3]  = Y[3];
        Luma[4]  = Y[2]; Luma[5]  = Y[2]; Luma[6]  = Y[2]; Luma[7]  = Y[2];
        Luma[8]  = Y[1]; Luma[9]  = Y[1]; Luma[10] = Y[1]; Luma[11] = Y[1];
        Luma[12] = Y[0]; Luma[13] = Y[0]; Luma[14] = Y[0]; Luma[15] = Y[0];
        break;
    case 5:
        Luma[0]  = Y[3]; Luma[1]  = Y[3]; Luma[2]  = Y[3]; Luma[3]  = Y[2];
        Luma[4]  = Y[3]; Luma[5]  = Y[2]; Luma[6]  = Y[2]; Luma[7]  = Y[1];
        Luma[8]  = Y[2]; Luma[9]  = Y[1]; Luma[10] = Y[1]; Luma[11] = Y[0];
        Luma[12] = Y[1]; Luma[13] = Y[0]; Luma[14] = Y[0]; Luma[15] = Y[0];
        break;
    case 6:
        Luma[0]  = Y[3]; Luma[1]  = Y[3]; Luma[2]  = Y[2]; Luma[3]  = Y[2];
        Luma[4]  = Y[3]; Luma[5]  = Y[2]; Luma[6]  = Y[1]; Luma[7]  = Y[1];
        Luma[8]  = Y[2]; Luma[9]  = Y[2]; Luma[10] = Y[1]; Luma[11] = Y[0];
        Luma[12] = Y[1]; Luma[13] = Y[1]; Luma[14] = Y[0]; Luma[15] = Y[0];
        break;
    case 7:
        Luma[0]  = Y[3]; Luma[1]  = Y[3]; Luma[2]  = Y[2]; Luma[3]  = Y[1];
        Luma[4]  = Y[3]; Luma[5]  = Y[2]; Luma[6]  = Y[1]; Luma[7]  = Y[0];
        Luma[8]  = Y[3]; Luma[9]  = Y[2]; Luma[10] = Y[1]; Luma[11] = Y[0];
        Luma[12] = Y[2]; Luma[13] = Y[1]; Luma[14] = Y[0]; Luma[15] = Y[0];
        break;
    default:
        Luma[0]  = Y[0]; Luma[1]  = Y[0]; Luma[2]  = Y[1]; Luma[3]  = Y[1];
        Luma[4]  = Y[0]; Luma[5]  = Y[0]; Luma[6]  = Y[1]; Luma[7]  = Y[1];
        Luma[8]  = Y[2]; Luma[9]  = Y[2]; Luma[10] = Y[3]; Luma[11] = Y[3];
        Luma[12] = Y[2]; Luma[13] = Y[2]; Luma[14] = Y[3]; Luma[15] = Y[3];
        break;
    }

    ulti_convert_yuv(frame, x, y, Luma, chroma);
}