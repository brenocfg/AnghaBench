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
struct radeon_encoder {int encoder_id; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 138 
#define  ENCODER_OBJECT_ID_INTERNAL_DVO1 137 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 136 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 135 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 134 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 133 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 128 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool radeon_dig_encoder(struct drm_encoder *encoder)
{
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_LVDS:
	case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
	case ENCODER_OBJECT_ID_INTERNAL_DVO1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
	case ENCODER_OBJECT_ID_INTERNAL_DDI:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		return true;
	}
	return false;
}