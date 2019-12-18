#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__* ransac_err; } ;
struct TYPE_10__ {float* s; } ;
struct TYPE_11__ {TYPE_1__ p2; } ;
struct TYPE_12__ {TYPE_2__ p; } ;
typedef  TYPE_3__ MotionVector ;
typedef  TYPE_4__ DeshakeOpenCLContext ;

/* Variables and functions */
 int /*<<< orphan*/  compute_error (TYPE_3__*,int const,double*,scalar_t__*) ; 
 int /*<<< orphan*/  run_estimate_kernel (TYPE_3__*,double*) ; 

__attribute__((used)) static void optimize_model(
    DeshakeOpenCLContext *deshake_ctx,
    MotionVector *best_pairs,
    MotionVector *inliers,
    const int num_inliers,
    float best_err,
    double *model_out
) {
    float move_x_val = 0.01;
    float move_y_val = 0.01;
    bool move_x = true;
    float old_move_x_val = 0;
    double model[6];
    int last_changed = 0;

    for (int iters = 0; iters < 200; iters++) {
        float total_err = 0;

        if (move_x) {
            best_pairs[0].p.p2.s[0] += move_x_val;
        } else {
            best_pairs[0].p.p2.s[0] += move_y_val;
        }

        run_estimate_kernel(best_pairs, model);
        compute_error(inliers, num_inliers, model, deshake_ctx->ransac_err);

        for (int j = 0; j < num_inliers; j++) {
            total_err += deshake_ctx->ransac_err[j];
        }

        if (total_err < best_err) {
            for (int mi = 0; mi < 6; ++mi) {
                model_out[mi] = model[mi];
            }

            best_err = total_err;
            last_changed = iters;
        } else {
            // Undo the change
            if (move_x) {
                best_pairs[0].p.p2.s[0] -= move_x_val;
            } else {
                best_pairs[0].p.p2.s[0] -= move_y_val;
            }

            if (iters - last_changed > 4) {
                // We've already improved the model as much as we can
                break;
            }

            old_move_x_val = move_x_val;

            if (move_x) {
                move_x_val *= -1;
            } else {
                move_y_val *= -1;
            }

            if (old_move_x_val < 0) {
                move_x = false;
            } else {
                move_x = true;
            }
        }
    }
}