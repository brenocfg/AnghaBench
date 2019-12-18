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
typedef  int /*<<< orphan*/  key ;
typedef  enum gfx_scale_type { ____Placeholder_gfx_scale_type } gfx_scale_type ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int RARCH_SCALE_ABSOLUTE ; 
 int /*<<< orphan*/  config_set_float (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  config_set_int (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  config_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scale_type_to_str (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,unsigned int) ; 

__attribute__((used)) static void shader_write_scale_dim(config_file_t *conf,
      const char *dim,
      enum gfx_scale_type type, float scale,
      unsigned absolute, unsigned i)
{
   char key[64];

   key[0] = '\0';

   snprintf(key, sizeof(key), "scale_type_%s%u", dim, i);
   config_set_string(conf, key, scale_type_to_str(type));

   snprintf(key, sizeof(key), "scale_%s%u", dim, i);
   if (type == RARCH_SCALE_ABSOLUTE)
      config_set_int(conf, key, absolute);
   else
      config_set_float(conf, key, scale);
}