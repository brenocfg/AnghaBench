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
#define  RETRO_LANGUAGE_ARABIC 145 
#define  RETRO_LANGUAGE_CHINESE_SIMPLIFIED 144 
#define  RETRO_LANGUAGE_CHINESE_TRADITIONAL 143 
#define  RETRO_LANGUAGE_DUTCH 142 
#define  RETRO_LANGUAGE_ESPERANTO 141 
#define  RETRO_LANGUAGE_FRENCH 140 
#define  RETRO_LANGUAGE_GERMAN 139 
#define  RETRO_LANGUAGE_GREEK 138 
#define  RETRO_LANGUAGE_ITALIAN 137 
#define  RETRO_LANGUAGE_JAPANESE 136 
#define  RETRO_LANGUAGE_KOREAN 135 
#define  RETRO_LANGUAGE_POLISH 134 
#define  RETRO_LANGUAGE_PORTUGUESE_BRAZIL 133 
#define  RETRO_LANGUAGE_PORTUGUESE_PORTUGAL 132 
#define  RETRO_LANGUAGE_RUSSIAN 131 
#define  RETRO_LANGUAGE_SPANISH 130 
#define  RETRO_LANGUAGE_TURKISH 129 
#define  RETRO_LANGUAGE_VIETNAMESE 128 
 char* msg_hash_to_str_ar (int) ; 
 char* msg_hash_to_str_chs (int) ; 
 char* msg_hash_to_str_cht (int) ; 
 char* msg_hash_to_str_de (int) ; 
 char* msg_hash_to_str_el (int) ; 
 char* msg_hash_to_str_eo (int) ; 
 char* msg_hash_to_str_es (int) ; 
 char* msg_hash_to_str_fr (int) ; 
 char* msg_hash_to_str_it (int) ; 
 char* msg_hash_to_str_jp (int) ; 
 char* msg_hash_to_str_ko (int) ; 
 char* msg_hash_to_str_nl (int) ; 
 char* msg_hash_to_str_pl (int) ; 
 char* msg_hash_to_str_pt_br (int) ; 
 char* msg_hash_to_str_pt_pt (int) ; 
 char* msg_hash_to_str_ru (int) ; 
 char* msg_hash_to_str_tr (int) ; 
 char const* msg_hash_to_str_us (int) ; 
 char* msg_hash_to_str_vn (int) ; 
 int /*<<< orphan*/  string_is_equal (char const*,char*) ; 
 int uint_user_language ; 

const char *msg_hash_to_str(enum msg_hash_enums msg)
{
   const char *ret = NULL;

#ifdef HAVE_LANGEXTRA
   switch (uint_user_language)
   {
      case RETRO_LANGUAGE_FRENCH:
         ret = msg_hash_to_str_fr(msg);
         break;
      case RETRO_LANGUAGE_GERMAN:
         ret = msg_hash_to_str_de(msg);
         break;
      case RETRO_LANGUAGE_SPANISH:
         ret = msg_hash_to_str_es(msg);
         break;
      case RETRO_LANGUAGE_ITALIAN:
         ret = msg_hash_to_str_it(msg);
         break;
      case RETRO_LANGUAGE_PORTUGUESE_BRAZIL:
         ret = msg_hash_to_str_pt_br(msg);
         break;
      case RETRO_LANGUAGE_PORTUGUESE_PORTUGAL:
         ret = msg_hash_to_str_pt_pt(msg);
         break;
      case RETRO_LANGUAGE_DUTCH:
         ret = msg_hash_to_str_nl(msg);
         break;
      case RETRO_LANGUAGE_ESPERANTO:
         ret = msg_hash_to_str_eo(msg);
         break;
      case RETRO_LANGUAGE_POLISH:
         ret = msg_hash_to_str_pl(msg);
         break;
      case RETRO_LANGUAGE_RUSSIAN:
         ret = msg_hash_to_str_ru(msg);
         break;
      case RETRO_LANGUAGE_JAPANESE:
         ret = msg_hash_to_str_jp(msg);
         break;
      case RETRO_LANGUAGE_KOREAN:
         ret = msg_hash_to_str_ko(msg);
         break;
      case RETRO_LANGUAGE_VIETNAMESE:
         ret = msg_hash_to_str_vn(msg);
         break;
      case RETRO_LANGUAGE_CHINESE_SIMPLIFIED:
         ret = msg_hash_to_str_chs(msg);
         break;
      case RETRO_LANGUAGE_CHINESE_TRADITIONAL:
         ret = msg_hash_to_str_cht(msg);
         break;
      case RETRO_LANGUAGE_ARABIC:
         ret = msg_hash_to_str_ar(msg);
         break;
      case RETRO_LANGUAGE_GREEK:
         ret = msg_hash_to_str_el(msg);
         break;
      case RETRO_LANGUAGE_TURKISH:
         ret = msg_hash_to_str_tr(msg);
         break;
      default:
         break;
   }
#endif

   if (ret && !string_is_equal(ret, "null"))
      return ret;

   return msg_hash_to_str_us(msg);
}