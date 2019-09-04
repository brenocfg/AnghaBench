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
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {scalar_t__ top_n; scalar_t__ structs; int features; scalar_t__ level; scalar_t__ min_eigen; scalar_t__ min_forward_backward_error; scalar_t__ bad_patches; scalar_t__ interval; int shift; int validate_set; double nnc_same; double nnc_thres; double nnc_verify; double nnc_beyond; double nnc_collect; scalar_t__ new_deform; scalar_t__ track_deform; scalar_t__ new_deform_angle; scalar_t__ track_deform_angle; scalar_t__ new_deform_scale; scalar_t__ track_deform_scale; scalar_t__ new_deform_shift; scalar_t__ track_deform_shift; scalar_t__ rotation; TYPE_1__ win_size; } ;
typedef  TYPE_2__ ccv_tld_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void _ccv_tld_check_params(ccv_tld_param_t params)
{
	assert(params.top_n > 0);
	assert(params.structs > 0);
	assert(params.features > 0 && params.features <= 32);
	assert(params.win_size.width > 0 && params.win_size.height > 0);
	assert((params.win_size.width & 1) == 1 && (params.win_size.height & 1) == 1);
	assert(params.level >= 0);
	assert(params.min_eigen > 0);
	assert(params.min_forward_backward_error > 0);
	assert(params.bad_patches > 0);
	assert(params.interval >= 0);
	assert(params.shift > 0 && params.shift < 1);
	assert(params.validate_set > 0 && params.validate_set < 1);
	assert(params.nnc_same > 0.5 && params.nnc_same < 1);
	assert(params.nnc_thres > 0.5 && params.nnc_thres < 1);
	assert(params.nnc_verify > 0.5 && params.nnc_verify < 1);
	assert(params.nnc_beyond > 0.5 && params.nnc_beyond < 1);
	assert(params.nnc_collect >= 0.5 && params.nnc_collect < 1);
	assert(params.new_deform > 0);
	assert(params.track_deform > 0);
	assert(params.new_deform_angle > 0);
	assert(params.track_deform_angle > 0);
	assert(params.new_deform_scale > 0);
	assert(params.track_deform_scale > 0);
	assert(params.new_deform_shift > 0);
	assert(params.track_deform_shift > 0);
	assert(params.rotation >= 0);
}