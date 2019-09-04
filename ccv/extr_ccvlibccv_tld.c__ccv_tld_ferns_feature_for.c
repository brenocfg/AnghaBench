#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dsfmt_t ;
struct TYPE_19__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_3__ ccv_rect_t ;
typedef  int /*<<< orphan*/  ccv_ferns_t ;
struct TYPE_20__ {scalar_t__ cols; scalar_t__ rows; int /*<<< orphan*/  step; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;
struct TYPE_21__ {int y; int x; } ;
typedef  TYPE_5__ ccv_decimal_point_t ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_22__ {TYPE_2__ classification; TYPE_1__ rect; } ;
typedef  TYPE_6__ ccv_comp_t ;

/* Variables and functions */
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 float CCV_PI ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_decimal_point (float,float) ; 
 TYPE_4__ ccv_dense_matrix (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_ferns_feature (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_get_dense_matrix_cell (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_4__*) ; 
 double ccv_max (int,double) ; 
 double ccv_min (int,int) ; 
 int /*<<< orphan*/  ccv_perspective_transform (TYPE_4__*,TYPE_4__**,int /*<<< orphan*/ ,float,float,float,float,float,float,float,float,float) ; 
 TYPE_5__ ccv_perspective_transform_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,float,float,float,float,float,float,float) ; 
 TYPE_3__ ccv_rect (int,int,int,int) ; 
 int /*<<< orphan*/  ccv_size (float,float) ; 
 float cosf (float) ; 
 float dsfmt_genrand_close_open (int /*<<< orphan*/ *) ; 
 float sinf (float) ; 

__attribute__((used)) static void _ccv_tld_ferns_feature_for(ccv_ferns_t* ferns, ccv_dense_matrix_t* a, ccv_comp_t box, uint32_t* fern, dsfmt_t* dsfmt, float deform_angle, float deform_scale, float deform_shift)
{
	assert(box.rect.x >= 0 && box.rect.x < a->cols);
	assert(box.rect.y >= 0 && box.rect.y < a->rows);
	assert(box.rect.x + box.rect.width <= a->cols);
	assert(box.rect.y + box.rect.height <= a->rows);
	if (!dsfmt)
	{
		ccv_dense_matrix_t roi = ccv_dense_matrix(box.rect.height, box.rect.width, CCV_GET_DATA_TYPE(a->type) | CCV_GET_CHANNEL(a->type), ccv_get_dense_matrix_cell(a, box.rect.y, box.rect.x, 0), 0);
		roi.step = a->step;
		ccv_ferns_feature(ferns, &roi, box.classification.id, fern);
	} else {
		float rotate_x = (deform_angle * 2 * dsfmt_genrand_close_open(dsfmt) - deform_angle) * CCV_PI / 180;
		float rotate_y = (deform_angle * 2 * dsfmt_genrand_close_open(dsfmt) - deform_angle) * CCV_PI / 180;
		float rotate_z = (deform_angle * 2 * dsfmt_genrand_close_open(dsfmt) - deform_angle) * CCV_PI / 180;
		float scale = 1 + deform_scale  - deform_scale * 2 * dsfmt_genrand_close_open(dsfmt);
		float m00 = cosf(rotate_z) * scale;
		float m01 = cosf(rotate_y) * sinf(rotate_z) * scale;
		float m02 = (deform_shift * 2 * dsfmt_genrand_close_open(dsfmt) - deform_shift) * box.rect.width;
		float m10 = (sinf(rotate_y) * cosf(rotate_z) - cosf(rotate_x) * sinf(rotate_z)) * scale;
		float m11 = (sinf(rotate_y) * sinf(rotate_z) + cosf(rotate_x) * cosf(rotate_z)) * scale;
		float m12 = (deform_shift * dsfmt_genrand_close_open(dsfmt) - deform_shift) * box.rect.height;
		float m20 = (sinf(rotate_y) * cosf(rotate_z) + sinf(rotate_x) * sinf(rotate_z)) * scale;
		float m21 = (sinf(rotate_y) * sinf(rotate_z) - sinf(rotate_x) * cosf(rotate_z)) * scale;
		float m22 = cosf(rotate_x) * cosf(rotate_y);
		ccv_decimal_point_t p00 = ccv_perspective_transform_apply(ccv_decimal_point(0, 0), ccv_size(box.rect.width, box.rect.height), m00, m01, m02, m10, m11, m12, m20, m21, m22);
		ccv_decimal_point_t p01 = ccv_perspective_transform_apply(ccv_decimal_point(box.rect.width, 0), ccv_size(box.rect.width, box.rect.height), m00, m01, m02, m10, m11, m12, m20, m21, m22);
		ccv_decimal_point_t p10 = ccv_perspective_transform_apply(ccv_decimal_point(0, box.rect.height), ccv_size(box.rect.width, box.rect.height), m00, m01, m02, m10, m11, m12, m20, m21, m22);
		ccv_decimal_point_t p11 = ccv_perspective_transform_apply(ccv_decimal_point(box.rect.width, box.rect.height), ccv_size(box.rect.width, box.rect.height), m00, m01, m02, m10, m11, m12, m20, m21, m22);
		int padding_top = (int)(ccv_max(0, -ccv_min(p00.y, p01.y)) + 0.5) + 5;
		padding_top = box.rect.y - ccv_max(box.rect.y - padding_top, 0);
		int padding_right = (int)(ccv_max(0, ccv_max(p01.x, p11.x) - box.rect.width) + 0.5) + 5;
		padding_right = ccv_min(box.rect.x + box.rect.width + padding_right, a->cols) - (box.rect.x + box.rect.width);
		int padding_bottom = (int)(ccv_max(0, ccv_max(p10.y, p11.y) - box.rect.height) + 0.5) + 5;
		padding_bottom = ccv_min(box.rect.y + box.rect.height + padding_bottom, a->rows) - (box.rect.y + box.rect.height);
		int padding_left = (int)(ccv_max(0, -ccv_min(p00.x, p10.x)) + 0.5) + 5;
		padding_left = box.rect.x - ccv_max(box.rect.x - padding_left, 0);
		ccv_rect_t hull = ccv_rect(box.rect.x - padding_left, box.rect.y - padding_top,
								   box.rect.width + padding_left + padding_right,
								   box.rect.height + padding_top + padding_bottom);
		assert(hull.x >= 0 && hull.x < a->cols);
		assert(hull.y >= 0 && hull.y < a->rows);
		assert(hull.x + hull.width <= a->cols);
		assert(hull.y + hull.height <= a->rows);
		ccv_dense_matrix_t roi = ccv_dense_matrix(hull.height, hull.width, CCV_GET_DATA_TYPE(a->type) | CCV_GET_CHANNEL(a->type), ccv_get_dense_matrix_cell(a, hull.y, hull.x, 0), 0);
		roi.step = a->step;
		ccv_dense_matrix_t* b = 0;
		ccv_perspective_transform(&roi, &b, 0, m00, m01, m02, m10, m11, m12, m20, m21, m22);
		roi = ccv_dense_matrix(box.rect.height, box.rect.width, CCV_GET_DATA_TYPE(b->type) | CCV_GET_CHANNEL(b->type), ccv_get_dense_matrix_cell(b, padding_top, padding_left, 0), 0);
		roi.step = b->step;
		ccv_ferns_feature(ferns, &roi, box.classification.id, fern);
		ccv_matrix_free(b);
	}
}