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
typedef  unsigned int uint64_t ;
struct drm_mode_fb_cmd2 {int width; int height; unsigned int* pitches; unsigned int* offsets; int /*<<< orphan*/ * handles; int /*<<< orphan*/  pixel_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,unsigned int,...) ; 
 int EINVAL ; 
 int ERANGE ; 
 unsigned int UINT_MAX ; 
 int drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int drm_format_num_planes (int /*<<< orphan*/ ) ; 
 unsigned int drm_format_plane_cpp (int /*<<< orphan*/ ,int) ; 
 int drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int format_check (struct drm_mode_fb_cmd2 const*) ; 

__attribute__((used)) static int framebuffer_check(const struct drm_mode_fb_cmd2 *r)
{
	int ret, hsub, vsub, num_planes, i;

	ret = format_check(r);
	if (ret) {
		DRM_DEBUG_KMS("bad framebuffer format 0x%08x\n", r->pixel_format);
		return ret;
	}

	hsub = drm_format_horz_chroma_subsampling(r->pixel_format);
	vsub = drm_format_vert_chroma_subsampling(r->pixel_format);
	num_planes = drm_format_num_planes(r->pixel_format);

	if (r->width == 0 || r->width % hsub) {
		DRM_DEBUG_KMS("bad framebuffer width %u\n", r->height);
		return -EINVAL;
	}

	if (r->height == 0 || r->height % vsub) {
		DRM_DEBUG_KMS("bad framebuffer height %u\n", r->height);
		return -EINVAL;
	}

	for (i = 0; i < num_planes; i++) {
		unsigned int width = r->width / (i != 0 ? hsub : 1);
		unsigned int height = r->height / (i != 0 ? vsub : 1);
		unsigned int cpp = drm_format_plane_cpp(r->pixel_format, i);

		if (!r->handles[i]) {
			DRM_DEBUG_KMS("no buffer object handle for plane %d\n", i);
			return -EINVAL;
		}

		if ((uint64_t) width * cpp > UINT_MAX)
			return -ERANGE;

		if ((uint64_t) height * r->pitches[i] + r->offsets[i] > UINT_MAX)
			return -ERANGE;

		if (r->pitches[i] < width * cpp) {
			DRM_DEBUG_KMS("bad pitch %u for plane %d\n", r->pitches[i], i);
			return -EINVAL;
		}
	}

	return 0;
}