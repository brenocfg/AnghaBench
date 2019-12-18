#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; scalar_t__ buff; } ;
struct TYPE_11__ {char* buff; } ;
struct TYPE_10__ {unsigned int len; TYPE_2__* items; } ;
struct TYPE_12__ {TYPE_1__ binary; scalar_t__ uint_; TYPE_4__ string; TYPE_3__ map; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_5__ val; } ;
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;
struct TYPE_13__ {int analog_supported; int rumble_supported; int coop_supported; unsigned int edge_magazine_rating; unsigned int edge_magazine_issue; unsigned int famitsu_magazine_rating; unsigned int tgdb_rating; unsigned int max_users; unsigned int releasemonth; unsigned int releaseyear; unsigned int size; void* md5; void* sha1; int /*<<< orphan*/  crc32; void* edge_magazine_review; void* enhancement_hw; void* pegi_rating; void* cero_rating; void* elspa_rating; void* esrb_rating; void* bbfc_rating; void* franchise; void* origin; void* genre; void* description; void* name; void* rom_name; void* serial; int /*<<< orphan*/  developer; void* publisher; } ;
typedef  TYPE_6__ database_info_t ;
struct TYPE_9__ {struct rmsgpack_dom_value value; struct rmsgpack_dom_value key; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 scalar_t__ RDT_MAP ; 
 void* bin_to_hex_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ libretrodb_cursor_read_item (int /*<<< orphan*/ *,struct rmsgpack_dom_value*) ; 
 int /*<<< orphan*/  rmsgpack_dom_value_free (struct rmsgpack_dom_value*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  string_split (char const*,char*) ; 
 int /*<<< orphan*/  swap_if_little32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int database_cursor_iterate(libretrodb_cursor_t *cur,
      database_info_t *db_info)
{
   unsigned i;
   struct rmsgpack_dom_value item;
   const char* str                = NULL;

   if (libretrodb_cursor_read_item(cur, &item) != 0)
      return -1;

   if (item.type != RDT_MAP)
   {
      rmsgpack_dom_value_free(&item);
      return 1;
   }

   db_info->analog_supported       = -1;
   db_info->rumble_supported       = -1;
   db_info->coop_supported         = -1;

   for (i = 0; i < item.val.map.len; i++)
   {
      struct rmsgpack_dom_value *key = &item.val.map.items[i].key;
      struct rmsgpack_dom_value *val = &item.val.map.items[i].value;
      const char *val_string         = NULL;

      if (!key || !val)
         continue;

      val_string                     = val->val.string.buff;
      str                            = key->val.string.buff;

      if (string_is_equal(str, "publisher"))
      {
         if (!string_is_empty(val_string))
            db_info->publisher = strdup(val_string);
      }
      else if (string_is_equal(str, "developer"))
      {
         if (!string_is_empty(val_string))
            db_info->developer = string_split(val_string, "|");
      }
      else if (string_is_equal(str, "serial"))
      {
         if (!string_is_empty(val_string))
            db_info->serial = strdup(val_string);
      }
      else if (string_is_equal(str, "rom_name"))
      {
         if (!string_is_empty(val_string))
            db_info->rom_name = strdup(val_string);
      }
      else if (string_is_equal(str, "name"))
      {
         if (!string_is_empty(val_string))
            db_info->name = strdup(val_string);
      }
      else if (string_is_equal(str, "description"))
      {
         if (!string_is_empty(val_string))
            db_info->description = strdup(val_string);
      }
      else if (string_is_equal(str, "genre"))
      {
         if (!string_is_empty(val_string))
            db_info->genre = strdup(val_string);
      }
      else if (string_is_equal(str, "origin"))
      {
         if (!string_is_empty(val_string))
            db_info->origin = strdup(val_string);
      }
      else if (string_is_equal(str, "franchise"))
      {
         if (!string_is_empty(val_string))
            db_info->franchise = strdup(val_string);
      }
      else if (string_is_equal(str, "bbfc_rating"))
      {
         if (!string_is_empty(val_string))
            db_info->bbfc_rating = strdup(val_string);
      }
      else if (string_is_equal(str, "esrb_rating"))
      {
         if (!string_is_empty(val_string))
            db_info->esrb_rating = strdup(val_string);
      }
      else if (string_is_equal(str, "elspa_rating"))
      {
         if (!string_is_empty(val_string))
            db_info->elspa_rating = strdup(val_string);
      }
      else if (string_is_equal(str, "cero_rating"))
      {
         if (!string_is_empty(val_string))
            db_info->cero_rating          = strdup(val_string);
      }
      else if (string_is_equal(str, "pegi_rating"))
      {
         if (!string_is_empty(val_string))
            db_info->pegi_rating          = strdup(val_string);
      }
      else if (string_is_equal(str, "enhancement_hw"))
      {
         if (!string_is_empty(val_string))
            db_info->enhancement_hw       = strdup(val_string);
      }
      else if (string_is_equal(str, "edge_review"))
      {
         if (!string_is_empty(val_string))
            db_info->edge_magazine_review = strdup(val_string);
      }
      else if (string_is_equal(str, "edge_rating"))
         db_info->edge_magazine_rating    = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "edge_issue"))
         db_info->edge_magazine_issue     = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "famitsu_rating"))
         db_info->famitsu_magazine_rating = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "tgdb_rating"))
         db_info->tgdb_rating             = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "users"))
         db_info->max_users               = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "releasemonth"))
         db_info->releasemonth            = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "releaseyear"))
         db_info->releaseyear             = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "rumble"))
         db_info->rumble_supported        = (int)val->val.uint_;
      else if (string_is_equal(str, "coop"))
         db_info->coop_supported          = (int)val->val.uint_;
      else if (string_is_equal(str, "analog"))
         db_info->analog_supported        = (int)val->val.uint_;
      else if (string_is_equal(str, "size"))
         db_info->size                    = (unsigned)val->val.uint_;
      else if (string_is_equal(str, "crc"))
         db_info->crc32 = swap_if_little32(
               *(uint32_t*)val->val.binary.buff);
      else if (string_is_equal(str, "sha1"))
         db_info->sha1 = bin_to_hex_alloc(
               (uint8_t*)val->val.binary.buff, val->val.binary.len);
      else if (string_is_equal(str, "md5"))
         db_info->md5 = bin_to_hex_alloc(
               (uint8_t*)val->val.binary.buff, val->val.binary.len);
      else
      {
         RARCH_LOG("Unknown key: %s\n", str);
      }
   }

   rmsgpack_dom_value_free(&item);

   return 0;
}