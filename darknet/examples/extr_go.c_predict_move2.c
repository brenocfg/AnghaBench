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
typedef  int /*<<< orphan*/  network ;
typedef  int /*<<< orphan*/  image ;

/* Variables and functions */
 int /*<<< orphan*/  axpy_cpu (int,int,float*,int,float*,int) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,float*,int) ; 
 int /*<<< orphan*/  flip_image (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float_to_image (int,int,int,float*) ; 
 float* network_predict (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  rotate_image_cw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scal_cpu (int,int,float*,int) ; 

float predict_move2(network *net, float *board, float *move, int multi)
{
    float *output = network_predict(net, board);
    copy_cpu(19*19+1, output, 1, move, 1);
    float result = output[19*19 + 1];
    int i;
    if(multi){
        image bim = float_to_image(19, 19, 3, board);
        for(i = 1; i < 8; ++i){
            rotate_image_cw(bim, i);
            if(i >= 4) flip_image(bim);

            float *output = network_predict(net, board);
            image oim = float_to_image(19, 19, 1, output);
            result += output[19*19 + 1];

            if(i >= 4) flip_image(oim);
            rotate_image_cw(oim, -i);

            axpy_cpu(19*19+1, 1, output, 1, move, 1);

            if(i >= 4) flip_image(bim);
            rotate_image_cw(bim, -i);
        }
        result = result/8;
        scal_cpu(19*19+1, 1./8., move, 1);
    }
    for(i = 0; i < 19*19; ++i){
        if(board[i] || board[i+19*19]) move[i] = 0;
    }
    return result;
}