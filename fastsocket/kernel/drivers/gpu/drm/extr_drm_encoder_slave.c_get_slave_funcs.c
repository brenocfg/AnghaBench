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
struct drm_encoder_slave_funcs {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {struct drm_encoder_slave_funcs* slave_funcs; } ;

/* Variables and functions */
 TYPE_1__* to_encoder_slave (struct drm_encoder*) ; 

__attribute__((used)) static inline struct drm_encoder_slave_funcs *
get_slave_funcs(struct drm_encoder *enc)
{
	return to_encoder_slave(enc)->slave_funcs;
}