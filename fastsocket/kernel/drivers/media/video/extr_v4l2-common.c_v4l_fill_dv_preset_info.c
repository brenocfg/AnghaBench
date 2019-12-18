#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct v4l2_dv_preset_info   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_dv_enum_preset {size_t preset; int /*<<< orphan*/  name; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_dv_preset_info {int /*<<< orphan*/  width; int /*<<< orphan*/  height; char const* name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__ const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int v4l_fill_dv_preset_info(u32 preset, struct v4l2_dv_enum_preset *info)
{
	static const struct v4l2_dv_preset_info {
		u16 width;
		u16 height;
		const char *name;
	} dv_presets[] = {
		{ 0, 0, "Invalid" },		/* V4L2_DV_INVALID */
		{ 720,  480, "480p@59.94" },	/* V4L2_DV_480P59_94 */
		{ 720,  576, "576p@50" },	/* V4L2_DV_576P50 */
		{ 1280, 720, "720p@24" },	/* V4L2_DV_720P24 */
		{ 1280, 720, "720p@25" },	/* V4L2_DV_720P25 */
		{ 1280, 720, "720p@30" },	/* V4L2_DV_720P30 */
		{ 1280, 720, "720p@50" },	/* V4L2_DV_720P50 */
		{ 1280, 720, "720p@59.94" },	/* V4L2_DV_720P59_94 */
		{ 1280, 720, "720p@60" },	/* V4L2_DV_720P60 */
		{ 1920, 1080, "1080i@29.97" },	/* V4L2_DV_1080I29_97 */
		{ 1920, 1080, "1080i@30" },	/* V4L2_DV_1080I30 */
		{ 1920, 1080, "1080i@25" },	/* V4L2_DV_1080I25 */
		{ 1920, 1080, "1080i@50" },	/* V4L2_DV_1080I50 */
		{ 1920, 1080, "1080i@60" },	/* V4L2_DV_1080I60 */
		{ 1920, 1080, "1080p@24" },	/* V4L2_DV_1080P24 */
		{ 1920, 1080, "1080p@25" },	/* V4L2_DV_1080P25 */
		{ 1920, 1080, "1080p@30" },	/* V4L2_DV_1080P30 */
		{ 1920, 1080, "1080p@50" },	/* V4L2_DV_1080P50 */
		{ 1920, 1080, "1080p@60" },	/* V4L2_DV_1080P60 */
	};

	if (info == NULL || preset >= ARRAY_SIZE(dv_presets))
		return -EINVAL;

	info->preset = preset;
	info->width = dv_presets[preset].width;
	info->height = dv_presets[preset].height;
	strlcpy(info->name, dv_presets[preset].name, sizeof(info->name));
	return 0;
}