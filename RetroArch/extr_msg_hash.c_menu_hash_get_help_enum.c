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
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
#define  RETRO_LANGUAGE_ARABIC 144 
#define  RETRO_LANGUAGE_CHINESE_SIMPLIFIED 143 
#define  RETRO_LANGUAGE_CHINESE_TRADITIONAL 142 
#define  RETRO_LANGUAGE_DUTCH 141 
#define  RETRO_LANGUAGE_ESPERANTO 140 
#define  RETRO_LANGUAGE_FRENCH 139 
#define  RETRO_LANGUAGE_GERMAN 138 
#define  RETRO_LANGUAGE_GREEK 137 
#define  RETRO_LANGUAGE_ITALIAN 136 
#define  RETRO_LANGUAGE_JAPANESE 135 
#define  RETRO_LANGUAGE_KOREAN 134 
#define  RETRO_LANGUAGE_POLISH 133 
#define  RETRO_LANGUAGE_PORTUGUESE_BRAZIL 132 
#define  RETRO_LANGUAGE_PORTUGUESE_PORTUGAL 131 
#define  RETRO_LANGUAGE_SPANISH 130 
#define  RETRO_LANGUAGE_TURKISH 129 
#define  RETRO_LANGUAGE_VIETNAMESE 128 
 int menu_hash_get_help_ar_enum (int,char*,size_t) ; 
 int menu_hash_get_help_chs_enum (int,char*,size_t) ; 
 int menu_hash_get_help_cht_enum (int,char*,size_t) ; 
 int menu_hash_get_help_de_enum (int,char*,size_t) ; 
 int menu_hash_get_help_el_enum (int,char*,size_t) ; 
 int menu_hash_get_help_eo_enum (int,char*,size_t) ; 
 int menu_hash_get_help_es_enum (int,char*,size_t) ; 
 int menu_hash_get_help_fr_enum (int,char*,size_t) ; 
 int menu_hash_get_help_it_enum (int,char*,size_t) ; 
 int menu_hash_get_help_jp_enum (int,char*,size_t) ; 
 int menu_hash_get_help_ko_enum (int,char*,size_t) ; 
 int menu_hash_get_help_nl_enum (int,char*,size_t) ; 
 int menu_hash_get_help_pl_enum (int,char*,size_t) ; 
 int menu_hash_get_help_pt_br_enum (int,char*,size_t) ; 
 int menu_hash_get_help_pt_pt_enum (int,char*,size_t) ; 
 int menu_hash_get_help_tr_enum (int,char*,size_t) ; 
 int menu_hash_get_help_us_enum (int,char*,size_t) ; 
 int menu_hash_get_help_vn_enum (int,char*,size_t) ; 
 int uint_user_language ; 

int menu_hash_get_help_enum(enum msg_hash_enums msg, char *s, size_t len)
{
#ifdef HAVE_MENU
   int ret = -1;

#ifdef HAVE_LANGEXTRA
   switch (uint_user_language)
   {
      case RETRO_LANGUAGE_FRENCH:
         ret = menu_hash_get_help_fr_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_GERMAN:
         ret = menu_hash_get_help_de_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_SPANISH:
         ret = menu_hash_get_help_es_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_ITALIAN:
         ret = menu_hash_get_help_it_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_PORTUGUESE_BRAZIL:
         ret = menu_hash_get_help_pt_br_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_PORTUGUESE_PORTUGAL:
         ret = menu_hash_get_help_pt_pt_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_DUTCH:
         ret = menu_hash_get_help_nl_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_ESPERANTO:
         ret = menu_hash_get_help_eo_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_POLISH:
         ret = menu_hash_get_help_pl_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_JAPANESE:
         ret = menu_hash_get_help_jp_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_KOREAN:
         ret = menu_hash_get_help_ko_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_VIETNAMESE:
         ret = menu_hash_get_help_vn_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_CHINESE_SIMPLIFIED:
         ret = menu_hash_get_help_chs_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_CHINESE_TRADITIONAL:
         ret = menu_hash_get_help_cht_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_ARABIC:
         ret = menu_hash_get_help_ar_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_GREEK:
         ret = menu_hash_get_help_el_enum(msg, s, len);
         break;
      case RETRO_LANGUAGE_TURKISH:
         ret = menu_hash_get_help_tr_enum(msg, s, len);
         break;
      default:
         break;
   }
#endif

   if (ret == 0)
      return ret;

   return menu_hash_get_help_us_enum(msg, s, len);
#else
   return 0;
#endif
}