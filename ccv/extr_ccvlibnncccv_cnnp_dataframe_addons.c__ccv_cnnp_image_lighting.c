#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float* f32; } ;
struct TYPE_5__ {int rows; int cols; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 scalar_t__ CCV_32F ; 
 scalar_t__ CCV_C3 ; 
 scalar_t__ CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 float ccv_clamp (float,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _ccv_cnnp_image_lighting(ccv_dense_matrix_t* image, const float alpha_r, const float alpha_g, const float alpha_b)
{
	assert(CCV_GET_DATA_TYPE(image->type) == CCV_32F);
	assert(CCV_GET_CHANNEL(image->type) == CCV_C3);
	// These eigenvector values can be computed out of imageNet dataset (see ccv_convnet for how that is done). Here I just copied
	// from mxnet: https://github.com/apache/incubator-mxnet/blob/master/src/operator/image/image_random-inl.h#L632
	const float pca_r = alpha_r * (55.46 * -0.5675) + alpha_g * (4.794 * 0.7192) + alpha_b * (1.148 * 0.4009);
	const float pca_g = alpha_r * (55.46 * -0.5808) + alpha_g * (4.794 * -0.0045) + alpha_b * (1.148 * -0.8140);
	const float pca_b = alpha_r * (55.46 * -0.5836) + alpha_g * (4.794 * -0.6948) + alpha_b * (1.148 * 0.4203);
	int i;
	const int size = image->rows * image->cols;
	float* const ptr = image->data.f32;
	for (i = 0; i < size; i++)
	{
		ptr[i * 3] = ccv_clamp(ptr[i * 3] + pca_r, 0, 255);
		ptr[i * 3 + 1] = ccv_clamp(ptr[i * 3 + 1] + pca_g, 0, 255);
		ptr[i * 3 + 2] = ccv_clamp(ptr[i * 3 + 2] + pca_b, 0, 255);
	}
}