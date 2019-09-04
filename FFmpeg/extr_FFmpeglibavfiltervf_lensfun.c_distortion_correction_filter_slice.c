#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int height; int width; int mode; int interpolation_type; float* distortion_coords; int* data_out; int linesize_out; int* data_in; int linesize_in; float* interpolation; } ;
typedef  TYPE_1__ DistortionCorrectionThreadData ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int GEOMETRY_DISTORTION ; 
#define  LANCZOS 130 
 float LANCZOS_RESOLUTION ; 
#define  LINEAR 129 
#define  NEAREST 128 
 int SUBPIXEL_DISTORTION ; 
 float square (float) ; 

__attribute__((used)) static int distortion_correction_filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    const DistortionCorrectionThreadData *thread_data = arg;
    const int slice_start = thread_data->height *  jobnr      / nb_jobs;
    const int slice_end   = thread_data->height * (jobnr + 1) / nb_jobs;

    int x, y, i, j, rgb_index;
    float interpolated, new_x, new_y, d, norm;
    int new_x_int, new_y_int;
    for (y = slice_start; y < slice_end; ++y)
        for (x = 0; x < thread_data->width; ++x)
            for (rgb_index = 0; rgb_index < 3; ++rgb_index) {
                if (thread_data->mode & SUBPIXEL_DISTORTION) {
                    // subpixel (and possibly geometry) distortion correction was applied, correct distortion
                    switch(thread_data->interpolation_type) {
                    case NEAREST:
                        new_x_int = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2]     + 0.5f;
                        new_y_int = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2 + 1] + 0.5f;
                        if (new_x_int < 0 || new_x_int >= thread_data->width || new_y_int < 0 || new_y_int >= thread_data->height) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = thread_data->data_in[new_x_int * 3 + rgb_index + new_y_int * thread_data->linesize_in];
                        }
                        break;
                    case LINEAR:
                        interpolated = 0.0f;
                        new_x = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2];
                        new_x_int = new_x;
                        new_y = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2 + 1];
                        new_y_int = new_y;
                        if (new_x_int < 0 || new_x_int + 1 >= thread_data->width || new_y_int < 0 || new_y_int + 1 >= thread_data->height) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] =
                                  thread_data->data_in[ new_x_int      * 3 + rgb_index +  new_y_int      * thread_data->linesize_in] * (new_x_int + 1 - new_x) * (new_y_int + 1 - new_y)
                                + thread_data->data_in[(new_x_int + 1) * 3 + rgb_index +  new_y_int      * thread_data->linesize_in] * (new_x - new_x_int) * (new_y_int + 1 - new_y)
                                + thread_data->data_in[ new_x_int      * 3 + rgb_index + (new_y_int + 1) * thread_data->linesize_in] * (new_x_int + 1 - new_x) * (new_y - new_y_int)
                                + thread_data->data_in[(new_x_int + 1) * 3 + rgb_index + (new_y_int + 1) * thread_data->linesize_in] * (new_x - new_x_int) * (new_y - new_y_int);
                        }
                        break;
                    case LANCZOS:
                        interpolated = 0.0f;
                        norm = 0.0f;
                        new_x = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2];
                        new_x_int = new_x;
                        new_y = thread_data->distortion_coords[x * 2 * 3 + y * thread_data->width * 2 * 3 + rgb_index * 2 + 1];
                        new_y_int = new_y;
                        for (j = 0; j < 4; ++j)
                            for (i = 0; i < 4; ++i) {
                                if (new_x_int + i - 2 < 0 || new_x_int + i - 2 >= thread_data->width || new_y_int + j - 2 < 0 || new_y_int + j - 2 >= thread_data->height)
                                    continue;
                                d = square(new_x - (new_x_int + i - 2)) * square(new_y - (new_y_int + j - 2));
                                if (d >= 4.0f)
                                    continue;
                                d = thread_data->interpolation[(int)(d * LANCZOS_RESOLUTION)];
                                norm += d;
                                interpolated += thread_data->data_in[(new_x_int + i - 2) * 3 + rgb_index + (new_y_int + j - 2) * thread_data->linesize_in] * d;
                            }
                        if (norm == 0.0f) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            interpolated /= norm;
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = interpolated < 0.0f ? 0.0f : interpolated > 255.0f ? 255.0f : interpolated;
                        }
                        break;
                    }
                } else if (thread_data->mode & GEOMETRY_DISTORTION) {
                    // geometry distortion correction was applied, correct distortion
                    switch(thread_data->interpolation_type) {
                    case NEAREST:
                        new_x_int = thread_data->distortion_coords[x * 2 + y * thread_data->width * 2]     + 0.5f;
                        new_y_int = thread_data->distortion_coords[x * 2 + y * thread_data->width * 2 + 1] + 0.5f;
                        if (new_x_int < 0 || new_x_int >= thread_data->width || new_y_int < 0 || new_y_int >= thread_data->height) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = thread_data->data_in[new_x_int * 3 + rgb_index + new_y_int * thread_data->linesize_in];
                        }
                        break;
                    case LINEAR:
                        interpolated = 0.0f;
                        new_x = thread_data->distortion_coords[x * 2 + y * thread_data->width * 2];
                        new_x_int = new_x;
                        new_y = thread_data->distortion_coords[x * 2 + y * thread_data->width * 2 + 1];
                        new_y_int = new_y;
                        if (new_x_int < 0 || new_x_int + 1 >= thread_data->width || new_y_int < 0 || new_y_int + 1 >= thread_data->height) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] =
                                  thread_data->data_in[ new_x_int      * 3 + rgb_index +  new_y_int      * thread_data->linesize_in] * (new_x_int + 1 - new_x) * (new_y_int + 1 - new_y)
                                + thread_data->data_in[(new_x_int + 1) * 3 + rgb_index +  new_y_int      * thread_data->linesize_in] * (new_x - new_x_int) * (new_y_int + 1 - new_y)
                                + thread_data->data_in[ new_x_int      * 3 + rgb_index + (new_y_int + 1) * thread_data->linesize_in] * (new_x_int + 1 - new_x) * (new_y - new_y_int)
                                + thread_data->data_in[(new_x_int + 1) * 3 + rgb_index + (new_y_int + 1) * thread_data->linesize_in] * (new_x - new_x_int) * (new_y - new_y_int);
                        }
                        break;
                    case LANCZOS:
                        interpolated = 0.0f;
                        norm = 0.0f;
                        new_x = thread_data->distortion_coords[x * 2     + y * thread_data->width * 2];
                        new_x_int = new_x;
                        new_y = thread_data->distortion_coords[x * 2 + 1 + y * thread_data->width * 2];
                        new_y_int = new_y;
                        for (j = 0; j < 4; ++j)
                            for (i = 0; i < 4; ++i) {
                                if (new_x_int + i - 2 < 0 || new_x_int + i - 2 >= thread_data->width || new_y_int + j - 2 < 0 || new_y_int + j - 2 >= thread_data->height)
                                    continue;
                                d = square(new_x - (new_x_int + i - 2)) * square(new_y - (new_y_int + j - 2));
                                if (d >= 4.0f)
                                    continue;
                                d = thread_data->interpolation[(int)(d * LANCZOS_RESOLUTION)];
                                norm += d;
                                interpolated += thread_data->data_in[(new_x_int + i - 2) * 3 + rgb_index + (new_y_int + j - 2) * thread_data->linesize_in] * d;
                            }
                        if (norm == 0.0f) {
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = 0;
                        } else {
                            interpolated /= norm;
                            thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = interpolated < 0.0f ? 0.0f : interpolated > 255.0f ? 255.0f : interpolated;
                        }
                        break;
                    }
                } else {
                    // no distortion correction was applied
                    thread_data->data_out[x * 3 + rgb_index + y * thread_data->linesize_out] = thread_data->data_in[x * 3 + rgb_index + y * thread_data->linesize_in];
                }
            }

    return 0;
}