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
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 int video_shader_get_type_from_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

enum rarch_shader_type video_shader_parse_type(const char *path)
{
   return video_shader_get_type_from_ext(path_get_extension(path), NULL);
}