#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* shader_path; } ;
typedef  TYPE_1__ d3d9_video_t ;

/* Variables and functions */
 int d3d9_init_multipass (TYPE_1__*,char const*) ; 
 int d3d9_init_singlepass (TYPE_1__*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static bool d3d9_process_shader(d3d9_video_t *d3d)
{
   const char *shader_path = d3d->shader_path;
   if (d3d && !string_is_empty(shader_path))
      return d3d9_init_multipass(d3d, shader_path);

   return d3d9_init_singlepass(d3d);
}