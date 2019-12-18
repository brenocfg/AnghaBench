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
struct string_list {int size; TYPE_1__* elems; } ;
struct overlay_desc {int type; char* next_index_name; float x; float y; float analog_saturate_pct; float range_x; float range_y; float mod_x; float mod_w; float mod_y; float mod_h; float alpha_mod; float range_mod; int movable; float delta_x; float delta_y; float range_x_mod; float range_y_mod; int /*<<< orphan*/  hitbox; int /*<<< orphan*/  button_mask; int /*<<< orphan*/  retro_key_idx; } ;
struct overlay {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  overlay_target_key ;
struct TYPE_5__ {int /*<<< orphan*/ * conf; } ;
typedef  TYPE_2__ overlay_loader_t ;
typedef  int /*<<< orphan*/  overlay_desc_normalized_key ;
typedef  int /*<<< orphan*/  overlay_desc_key ;
typedef  int /*<<< orphan*/  overlay_analog_saturate_key ;
typedef  int /*<<< orphan*/  overlay ;
typedef  int /*<<< orphan*/  config_file_t ;
typedef  int /*<<< orphan*/  conf_key ;
struct TYPE_4__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL (int /*<<< orphan*/ ) ; 
 scalar_t__ BIT256_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT256_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVERLAY_HITBOX_RADIAL ; 
 int /*<<< orphan*/  OVERLAY_HITBOX_RECT ; 
#define  OVERLAY_TYPE_ANALOG_LEFT 129 
#define  OVERLAY_TYPE_ANALOG_RIGHT 128 
 int OVERLAY_TYPE_BUTTONS ; 
 int OVERLAY_TYPE_KEYBOARD ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_OVERLAY_NEXT ; 
 int /*<<< orphan*/  config_get_array (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ config_get_bool (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ config_get_float (int /*<<< orphan*/ *,char*,float*) ; 
 int /*<<< orphan*/  input_config_translate_str_to_bind_id (char const*) ; 
 int /*<<< orphan*/  input_config_translate_str_to_rk (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ strtod (char const*,int /*<<< orphan*/ *) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static bool task_overlay_load_desc(
      overlay_loader_t *loader,
      struct overlay_desc *desc,
      struct overlay *input_overlay,
      unsigned ol_idx, unsigned desc_idx,
      unsigned width, unsigned height,
      bool normalized, float alpha_mod, float range_mod)
{
   float width_mod, height_mod;
   char overlay_desc_key[64];
   char conf_key[64];
   char overlay_desc_normalized_key[64];
   char overlay[256];
   float tmp_float                      = 0.0f;
   bool tmp_bool                        = false;
   bool ret                             = true;
   bool by_pixel                        = false;
   char *key                            = NULL;
   struct string_list *list             = NULL;
   const char *x                        = NULL;
   const char *y                        = NULL;
   const char *box                      = NULL;
   config_file_t *conf                  = loader->conf;

   overlay_desc_key[0] = conf_key[0] =
      overlay_desc_normalized_key[0] = overlay[0] = '\0';

   snprintf(overlay_desc_key, sizeof(overlay_desc_key),
         "overlay%u_desc%u", ol_idx, desc_idx);

   snprintf(overlay_desc_normalized_key, sizeof(overlay_desc_normalized_key),
         "overlay%u_desc%u_normalized", ol_idx, desc_idx);
   if (config_get_bool(conf, overlay_desc_normalized_key, &tmp_bool))
      normalized = tmp_bool;

   by_pixel = !normalized;

   if (by_pixel && (width == 0 || height == 0))
   {
      RARCH_ERR("[Overlay]: Base overlay is not set and not using normalized coordinates.\n");
      ret = false;
      goto end;
   }

   if (!config_get_array(conf, overlay_desc_key, overlay, sizeof(overlay)))
   {
      RARCH_ERR("[Overlay]: Didn't find key: %s.\n", overlay_desc_key);
      ret = false;
      goto end;
   }

   list = string_split(overlay, ", ");

   if (!list)
   {
      RARCH_ERR("[Overlay]: Failed to split overlay desc.\n");
      ret = false;
      goto end;
   }

   if (list->size < 6)
   {
      RARCH_ERR("[Overlay]: Overlay desc is invalid. Requires at least 6 tokens.\n");
      ret = false;
      goto end;
   }

   key            = list->elems[0].data;
   x              = list->elems[1].data;
   y              = list->elems[2].data;
   box            = list->elems[3].data;

   desc->retro_key_idx = 0;
   BIT256_CLEAR_ALL(desc->button_mask);

   if (string_is_equal(key, "analog_left"))
      desc->type          = OVERLAY_TYPE_ANALOG_LEFT;
   else if (string_is_equal(key, "analog_right"))
      desc->type          = OVERLAY_TYPE_ANALOG_RIGHT;
   else if (strstr(key, "retrok_") == key)
   {
      desc->type          = OVERLAY_TYPE_KEYBOARD;
      desc->retro_key_idx = input_config_translate_str_to_rk(key + 7);
   }
   else
   {
      char      *save = NULL;
      const char *tmp = strtok_r(key, "|", &save);

      desc->type = OVERLAY_TYPE_BUTTONS;

      for (; tmp; tmp = strtok_r(NULL, "|", &save))
      {
         if (!string_is_equal(tmp, "nul"))
            BIT256_SET(desc->button_mask, input_config_translate_str_to_bind_id(tmp));
      }

      if (BIT256_GET(desc->button_mask, RARCH_OVERLAY_NEXT))
      {
         char overlay_target_key[64];

         snprintf(overlay_target_key, sizeof(overlay_target_key),
               "overlay%u_desc%u_next_target", ol_idx, desc_idx);
         config_get_array(conf, overlay_target_key,
               desc->next_index_name, sizeof(desc->next_index_name));
      }
   }

   width_mod  = 1.0f;
   height_mod = 1.0f;

   if (by_pixel)
   {
      width_mod  /= width;
      height_mod /= height;
   }

   desc->x = (float)strtod(x, NULL) * width_mod;
   desc->y = (float)strtod(y, NULL) * height_mod;

   if (string_is_equal(box, "radial"))
      desc->hitbox = OVERLAY_HITBOX_RADIAL;
   else if (string_is_equal(box, "rect"))
      desc->hitbox = OVERLAY_HITBOX_RECT;
   else
   {
      RARCH_ERR("[Overlay]: Hitbox type (%s) is invalid. Use \"radial\" or \"rect\".\n", box);
      ret = false;
      goto end;
   }

   switch (desc->type)
   {
      case OVERLAY_TYPE_ANALOG_LEFT:
      case OVERLAY_TYPE_ANALOG_RIGHT:
         {
            char overlay_analog_saturate_key[64];

            overlay_analog_saturate_key[0] = '\0';

            if (desc->hitbox != OVERLAY_HITBOX_RADIAL)
            {
               RARCH_ERR("[Overlay]: Analog hitbox type must be \"radial\".\n");
               ret = false;
               goto end;
            }

            snprintf(overlay_analog_saturate_key,
                  sizeof(overlay_analog_saturate_key),
                  "overlay%u_desc%u_saturate_pct", ol_idx, desc_idx);
            if (config_get_float(conf, overlay_analog_saturate_key,
                     &tmp_float))
               desc->analog_saturate_pct = tmp_float;
            else
               desc->analog_saturate_pct = 1.0f;
         }
         break;
      default:
         /* OVERLAY_TYPE_BUTTONS  - unhandled */
         /* OVERLAY_TYPE_KEYBOARD - unhandled */
         break;
   }

   desc->range_x = (float)strtod(list->elems[4].data, NULL) * width_mod;
   desc->range_y = (float)strtod(list->elems[5].data, NULL) * height_mod;

   desc->mod_x   = desc->x - desc->range_x;
   desc->mod_w   = 2.0f * desc->range_x;
   desc->mod_y   = desc->y - desc->range_y;
   desc->mod_h   = 2.0f * desc->range_y;

   snprintf(conf_key, sizeof(conf_key),
         "overlay%u_desc%u_alpha_mod", ol_idx, desc_idx);
   desc->alpha_mod = alpha_mod;
   if (config_get_float(conf, conf_key, &tmp_float))
         desc->alpha_mod = tmp_float;

   snprintf(conf_key, sizeof(conf_key),
         "overlay%u_desc%u_range_mod", ol_idx, desc_idx);
   desc->range_mod = range_mod;
   if (config_get_float(conf, conf_key, &tmp_float))
      desc->range_mod = tmp_float;

   snprintf(conf_key, sizeof(conf_key),
         "overlay%u_desc%u_movable", ol_idx, desc_idx);
   desc->movable     = false;
   desc->delta_x     = 0.0f;
   desc->delta_y     = 0.0f;

   if (config_get_bool(conf, conf_key, &tmp_bool))
      desc->movable = tmp_bool;

   desc->range_x_mod = desc->range_x;
   desc->range_y_mod = desc->range_y;

   input_overlay->pos ++;

end:
   if (list)
      string_list_free(list);
   return ret;
}