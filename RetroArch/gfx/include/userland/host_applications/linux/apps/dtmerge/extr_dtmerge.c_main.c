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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int dtoverlay_apply_override (int /*<<< orphan*/ *,char*,void const*,int,char*) ; 
 int /*<<< orphan*/  dtoverlay_enable_debug (int) ; 
 void* dtoverlay_find_override (int /*<<< orphan*/ *,char*,int*) ; 
 int dtoverlay_fixup_overlay (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtoverlay_free_dtb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtoverlay_load_dtb (char const*,int) ; 
 int dtoverlay_merge_overlay (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtoverlay_pack_dtb (int /*<<< orphan*/ *) ; 
 int dtoverlay_save_dtb (int /*<<< orphan*/ *,char const*) ; 
 int dtoverlay_set_synonym (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
   const char *base_file;
   const char *merged_file;
   const char *overlay_file;
   DTBLOB_T *base_dtb;
   DTBLOB_T *overlay_dtb;
   int err;
   int argn = 1;
   int max_dtb_size = 100000;

   while ((argn < argc) && (argv[argn][0] == '-'))
   {
      const char *arg = argv[argn++];
      if ((strcmp(arg, "-d") == 0) ||
          (strcmp(arg, "--debug") == 0))
         dtoverlay_enable_debug(1);
      else if ((strcmp(arg, "-h") == 0) ||
          (strcmp(arg, "--help") == 0))
         usage();
      else
      {
         printf("* Unknown option '%s'\n", arg);
         usage();
      }
   }

   if (argc < (argn + 3))
   {
      usage();
   }

   base_file = argv[argn++];
   merged_file = argv[argn++];
   overlay_file = argv[argn++];

   base_dtb = dtoverlay_load_dtb(base_file, max_dtb_size);
   if (!base_dtb)
   {
       printf("* failed to load '%s'\n", base_file);
       return -1;
   }

   err = dtoverlay_set_synonym(base_dtb, "i2c", "i2c0");
   err = dtoverlay_set_synonym(base_dtb, "i2c_arm", "i2c0");
   err = dtoverlay_set_synonym(base_dtb, "i2c_vc", "i2c1");
   err = dtoverlay_set_synonym(base_dtb, "i2c_baudrate", "i2c0_baudrate");
   err = dtoverlay_set_synonym(base_dtb, "i2c_arm_baudrate", "i2c0_baudrate");
   err = dtoverlay_set_synonym(base_dtb, "i2c_vc_baudrate", "i2c1_baudrate");

   if (strcmp(overlay_file, "-") == 0)
   {
      overlay_dtb = base_dtb;
   }
   else
   {
      overlay_dtb = dtoverlay_load_dtb(overlay_file, max_dtb_size);
      if (overlay_dtb)
	  err = dtoverlay_fixup_overlay(base_dtb, overlay_dtb);
      else
	  err = -1;
   }

   while (!err && (argn < argc))
   {
      char *param_name = argv[argn++];
      char *param_value = param_name + strcspn(param_name, "=");
      const void *override_data;
      int data_len;

      if (*param_value == '=')
      {
         *(param_value++) = '\0';
      }
      else
      {
         /* This isn't a well-formed parameter assignment, but it can be
            treated as an assignment of true. */
         param_value = "true";
      }

      override_data = dtoverlay_find_override(overlay_dtb, param_name,
                                              &data_len);
      if (override_data)
      {
         err = dtoverlay_apply_override(overlay_dtb, param_name,
                                        override_data, data_len,
                                        param_value);
      }
      else
      {
         override_data = dtoverlay_find_override(base_dtb, param_name, &data_len);
         if (override_data)
         {
            err = dtoverlay_apply_override(base_dtb, param_name,
                                           override_data, data_len,
                                           param_value);
         }
         else
         {
            printf("* unknown param '%s'\n", param_name);
            err = data_len;
         }
      }
   }

   if (!err && (overlay_dtb != base_dtb))
   {
      err = dtoverlay_merge_overlay(base_dtb, overlay_dtb);

      dtoverlay_free_dtb(overlay_dtb);
   }

   if (!err)
   {
      dtoverlay_pack_dtb(base_dtb);
      err = dtoverlay_save_dtb(base_dtb, merged_file);
   }

   dtoverlay_free_dtb(base_dtb);

   if (err != 0)
      printf("* Exiting with error code %d\n", err);

   return err;
}