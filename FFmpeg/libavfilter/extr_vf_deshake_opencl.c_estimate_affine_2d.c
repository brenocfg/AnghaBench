#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int num_model_matches; TYPE_1__* model_matches; } ;
struct TYPE_12__ {int /*<<< orphan*/  ransac_err; int /*<<< orphan*/  alfg; } ;
struct TYPE_11__ {int should_consider; } ;
typedef  TYPE_1__ MotionVector ;
typedef  TYPE_2__ DeshakeOpenCLContext ;
typedef  TYPE_3__ DebugMatches ;

/* Variables and functions */
 int FFMAX (int const,int) ; 
 int find_inliers (TYPE_1__*,int const,double*,int /*<<< orphan*/ ,double const) ; 
 int get_subset (int /*<<< orphan*/ *,TYPE_1__*,int const,TYPE_1__*,int) ; 
 int ransac_update_num_iters (double const,double,int) ; 
 int /*<<< orphan*/  run_estimate_kernel (TYPE_1__*,double*) ; 

__attribute__((used)) static bool estimate_affine_2d(
    DeshakeOpenCLContext *deshake_ctx,
    MotionVector *point_pairs,
    DebugMatches *debug_matches,
    const int num_point_pairs,
    double *model_out,
    const double threshold,
    const int max_iters,
    const double confidence
) {
    bool result = false;
    double best_model[6], model[6];
    MotionVector pairs_subset[3], best_pairs[3];

    int iter, niters = FFMAX(max_iters, 1);
    int good_count, max_good_count = 0;

    // We need at least 3 points to build a model from
    if (num_point_pairs < 3) {
        return false;
    } else if (num_point_pairs == 3) {
        // There are only 3 points, so RANSAC doesn't apply here
        run_estimate_kernel(point_pairs, model_out);

        for (int i = 0; i < 3; ++i) {
            point_pairs[i].should_consider = true;
        }

        return true;
    }

    for (iter = 0; iter < niters; ++iter) {
        bool found = get_subset(&deshake_ctx->alfg, point_pairs, num_point_pairs, pairs_subset, 10000);

        if (!found) {
            if (iter == 0) {
                return false;
            }

            break;
        }

        run_estimate_kernel(pairs_subset, model);
        good_count = find_inliers(point_pairs, num_point_pairs, model, deshake_ctx->ransac_err, threshold);

        if (good_count > FFMAX(max_good_count, 2)) {
            for (int mi = 0; mi < 6; ++mi) {
                best_model[mi] = model[mi];
            }

            for (int pi = 0; pi < 3; pi++) {
                best_pairs[pi] = pairs_subset[pi];
            }

            max_good_count = good_count;
            niters = ransac_update_num_iters(
                confidence,
                (double)(num_point_pairs - good_count) / num_point_pairs,
                niters
            );
        }
    }

    if (max_good_count > 0) {
        for (int mi = 0; mi < 6; ++mi) {
            model_out[mi] = best_model[mi];
        }

        for (int pi = 0; pi < 3; ++pi) {
            debug_matches->model_matches[pi] = best_pairs[pi];
        }
        debug_matches->num_model_matches = 3;

        // Find the inliers again for the best model for debugging
        find_inliers(point_pairs, num_point_pairs, best_model, deshake_ctx->ransac_err, threshold);
        result = true;
    }

    return result;
}