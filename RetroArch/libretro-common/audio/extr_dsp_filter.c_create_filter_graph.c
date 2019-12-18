#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_dsp_instance {int /*<<< orphan*/  impl_data; TYPE_2__* impl; } ;
struct dspfilter_info {float input_rate; } ;
struct config_file_userdata {char** prefix; int /*<<< orphan*/  conf; } ;
struct TYPE_5__ {unsigned int num_instances; struct retro_dsp_instance* instances; int /*<<< orphan*/  conf; } ;
typedef  TYPE_1__ retro_dsp_filter_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_6__ {char* short_ident; int /*<<< orphan*/  (* init ) (struct dspfilter_info*,int /*<<< orphan*/ *,struct config_file_userdata*) ;} ;

/* Variables and functions */
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  config_get_array (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  config_get_uint (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  dspfilter_config ; 
 TYPE_2__* find_implementation (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct dspfilter_info*,int /*<<< orphan*/ *,struct config_file_userdata*) ; 

__attribute__((used)) static bool create_filter_graph(retro_dsp_filter_t *dsp, float sample_rate)
{
   unsigned i;
   struct retro_dsp_instance *instances = NULL;
   unsigned filters                     = 0;

   if (!config_get_uint(dsp->conf, "filters", &filters))
      return false;

   instances = (struct retro_dsp_instance*)calloc(filters, sizeof(*instances));
   if (!instances)
      return false;

   dsp->instances     = instances;
   dsp->num_instances = filters;

   for (i = 0; i < filters; i++)
   {
      struct config_file_userdata userdata;
      struct dspfilter_info info;
      char key[64];
      char name[64];

      key[0] = name[0] = '\0';

      info.input_rate  = sample_rate;

      snprintf(key, sizeof(key), "filter%u", i);

      if (!config_get_array(dsp->conf, key, name, sizeof(name)))
         return false;

      dsp->instances[i].impl = find_implementation(dsp, name);
      if (!dsp->instances[i].impl)
         return false;

      userdata.conf = dsp->conf;
      /* Index-specific configs take priority over ident-specific. */
      userdata.prefix[0] = key;
      userdata.prefix[1] = dsp->instances[i].impl->short_ident;

      dsp->instances[i].impl_data = dsp->instances[i].impl->init(&info,
            &dspfilter_config, &userdata);
      if (!dsp->instances[i].impl_data)
         return false;
   }

   return true;
}